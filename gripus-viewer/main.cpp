#include <stdlib.h>
#include <iostream>
#include <string>

#include <cmath>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Simulation.h>
#include <Output.h>

#include "ShaderProgram.h"
#include "Renderer.h"

void callback_error(int error, const char* desc);
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_cursor(GLFWwindow * window, double x, double y);
void callback_mouse(GLFWwindow* window, int button, int action, int mods);
void callback_scroll(GLFWwindow* window, double x, double y);

Simulation* simulation;
Output* output;

double lastTime;
bool pause = true;

bool axis = true;
bool velocities = false;
float lineWidth = 2.0;

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Invalid command line arguments" << std::endl;
		std::cerr << "Usage: gripus-viewer %path_to_simulation %path_to_output" << std::endl;
		std::cerr << "       gripus-viewer --jit %path_to_simulation" << std::endl;
		std::cerr << std::endl;

		return EXIT_FAILURE;
	}

	if(std::string(argv[1])=="--jit") {
		simulation = Simulation::load(argv[2]);
		output = nullptr;
	} else {
		simulation = Simulation::load(argv[1]);
		output = new Output(simulation);
		output->load(argv[2]);
	}

	glfwSetErrorCallback(&callback_error);
	if (!glfwInit())
		return EXIT_FAILURE;

	//find out a few things about the projection
	float projection_width = (simulation->settings->projection->size[0][1] - simulation->settings->projection->size[0][0]);
	float projection_height = (simulation->settings->projection->size[1][1] - simulation->settings->projection->size[1][0]);
	float ratio = projection_width / projection_height;

	GLFWwindow* window = glfwCreateWindow((int)(640 * ratio), (int)640, (std::string("Simuation View: ") + argv[2]).c_str(), nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, &callback_key);
	glfwSetCursorPosCallback(window, &callback_cursor);
	glfwSetMouseButtonCallback(window, &callback_mouse);
	glfwSetScrollCallback(window, &callback_scroll);

	glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);
	glLineWidth(lineWidth);

	ShaderProgram* program = new ShaderProgram();
	program->vertexShader = Shader::load("shaders/vertex.shader", GL_VERTEX_SHADER);
	program->fragmentShader = Shader::load("shaders/fragment.shader", GL_FRAGMENT_SHADER);

	bool result = true;
	result &= program->vertexShader->compile(std::cerr);
	result &= program->fragmentShader->compile(std::cerr);
	if (!result)
		return EXIT_FAILURE;

	program->bind_location("vertex_position", 0);
	program->bind_location("vertex_normal", 1);
	program->bind_location("vertex_color", 2);
	program->bind_location("vertex_texuv", 3);

	result = program->link(std::cerr);
	if (!result)
		return EXIT_FAILURE;

	GLint camera = glGetUniformLocation(program->getProgram(), "camera");
	GLint model = glGetUniformLocation(program->getProgram(), "model");
	GLint hasTex = glGetUniformLocation(program->getProgram(), "hasTex");
	GLint tex = glGetUniformLocation(program->getProgram(), "tex");
	glUseProgram(program->getProgram());

	Renderer::initialize(simulation);

	glm::vec3 axis_data[3][2][2] = { {{{ -simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[0]), 0.f, 0.f },	{ 1.f, 0.f, 0.f }},
								{{ +simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[0]), 0.f, 0.f },	{ 1.f, 0.f, 0.f }}},

								{{{ 0.f, -simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[1]), 0.f },	{ 0.f, 1.f, 0.f }},
								{{ 0.f, +simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[1]), 0.f },	{ 0.f, 1.f, 0.f }}},

								{{{ 0.f, 0.f, -simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[2]) },	{ 0.f, 0.f, 1.f }},
								{{ 0.f, 0.f, +simulation->settings->projection->size[2][1]/(2*simulation->settings->projection->scale[2]) },	{ 0.f, 0.f, 1.f }}}
								};
	GLuint axis_vao, axis_vbo;
	glGenVertexArrays(1, &axis_vao);
	glGenBuffers(1, &axis_vbo);
	glBindVertexArray(axis_vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(axis_data), axis_data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (GLvoid*)0);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (GLvoid*)(sizeof(glm::vec3)));

	//for default, let 'em have their textures
	glUniform1i(hasTex, 1);

	float simtime = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		double delta = glfwGetTime() - lastTime;
		lastTime += delta;

		int fw, fh;
		glfwGetFramebufferSize(window, &fw, &fh);

		glViewport(0, 0, fw, fh);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection;
		glm::mat3x2 tmp = simulation->settings->projection->size;
		switch (simulation->settings->projection->type) {
		case Projection::ProjectionType::Parallel:
			projection = glm::ortho(tmp[0][0], tmp[0][1], tmp[1][0], tmp[1][0], tmp[2][0], tmp[2][1]);
			break;
		case Projection::ProjectionType::Perspective:
			projection = glm::frustum(tmp[0][0], tmp[0][1], tmp[1][0], tmp[1][1], tmp[2][0], tmp[2][1]);
			break;
		default:
			projection = glm::mat4(1.f);
			break;
		}
		glm::mat4 view = glm::lookAt(simulation->settings->view->eye, simulation->settings->view->center, simulation->settings->view->up);
		glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(projection * view * glm::scale(simulation->settings->projection->scale)));

		if(!pause)
			simtime += delta * simulation->settings->speed->boost;

		while(simulation->settings->time->getTime() < simtime) {
			if(output==nullptr)
				simulation->simulate_step();
			else
				output->read();

			simulation->settings->time->doStep();
		}

		if(axis) {
			glUniform1i(hasTex, 0);
			glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

			glBindVertexArray(axis_vao);
			glDrawArrays(GL_LINES, 0, 3*2);

			glUniform1i(hasTex, 1);
		}
		Renderer::render(model, hasTex, tex, velocities);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	Renderer::finalize();
	
	glfwDestroyWindow(window);
	glfwTerminate();

	delete simulation;
	delete output;

	return EXIT_SUCCESS;
}

void callback_error(int error, const char* desc) {
	std::cerr << "GLFW ERROR " << error << ": " << desc << std::endl;
}
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	double delta = glfwGetTime() - lastTime;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	static float directions[2];
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			directions[0] = (action == GLFW_PRESS ? 1.f : 0.f);
			break;
		case GLFW_KEY_S:
			directions[0] = (action == GLFW_PRESS ? -1.f : 0.f);
			break;
		case GLFW_KEY_A:
			directions[1] = (action == GLFW_PRESS ? -1.f : 0.f);
			break;
		case GLFW_KEY_D:
			directions[1] = (action == GLFW_PRESS ? 1.f : 0.f);
			break;

		case GLFW_KEY_P:
			pause = (action == GLFW_PRESS ? !pause : pause);
			break;
		case GLFW_KEY_I:
			simulation->settings->speed->boost *= (action == GLFW_PRESS ? 0.5f : 1.0f);
			break;
		case GLFW_KEY_O:
			simulation->settings->speed->boost *= (action == GLFW_PRESS ? 2.0f : 1.0f);
			break;

		case GLFW_KEY_X:
			axis = (action == GLFW_PRESS ? !axis : axis);
			break;
		case GLFW_KEY_V:
			velocities = (action == GLFW_PRESS ? !velocities : velocities);
			break;
		case GLFW_KEY_Z:
			lineWidth += (action == GLFW_PRESS ? -1.f : 0.f);
			if(lineWidth<1.f)
				lineWidth = 1.f;
			
			glLineWidth(lineWidth);
			break;
		case GLFW_KEY_C:
			lineWidth += (action == GLFW_PRESS ? +1.f : 0.f);
			glLineWidth(lineWidth);
			break;
		}
	}

	glm::vec3 displacement;
	displacement = glm::normalize(simulation->settings->view->center - simulation->settings->view->eye) * directions[0];
	displacement += glm::normalize(glm::cross(simulation->settings->view->center - simulation->settings->view->eye, simulation->settings->view->up)) * directions[1];

	displacement *= simulation->settings->view->step * (float)delta;

	simulation->settings->view->eye += displacement;
	simulation->settings->view->center += displacement;
}

bool cursorActive = false;
void callback_cursor(GLFWwindow * window, double x, double y) {
	if(!cursorActive)
		return;

	double delta = glfwGetTime() - lastTime;

	int fw, fh;
	glfwGetFramebufferSize(window, &fw, &fh);

	x = x / fw - 0.5f; x *= delta * 90; /* to degs */
	y = y / fw - 0.5f; y *= delta * 90; /* to degs */

	glm::mat4 rotation = glm::rotate((float)x, glm::vec3(0.f, 1.f, 0.f));
	rotation *= glm::rotate((float)y, glm::vec3(1.f, 0.f, 0.f));

	glm::vec3 direction = (simulation->settings->view->center - simulation->settings->view->eye);
	direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
	simulation->settings->view->eye = simulation->settings->view->center + (-direction);

	glfwSetCursorPos(window, fw/2, fh/2);
}
void callback_mouse(GLFWwindow* window, int button, int action, int mods) {
	if (button==GLFW_MOUSE_BUTTON_1 && action==GLFW_PRESS) {
		if(cursorActive)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			int fw, fh;
			glfwGetFramebufferSize(window, &fw, &fh);
			glfwSetCursorPos(window, fw/2, fh/2);
		}
		
		cursorActive = !cursorActive;
	}
}
void callback_scroll(GLFWwindow* window, double x, double y) {
	x *= simulation->settings->view->step;
	y *= simulation->settings->view->step;

	glm::vec3 displacement = simulation->settings->view->center - simulation->settings->view->eye;
	if (glm::length(displacement) <= simulation->settings->view->step && /* && we're scrolling in: */ (x > 0 || y > 0))
		displacement = glm::vec3(0.f, 0.f, 0.f); //we can not normalize a zero vector, do nothin' jon snow, just leave it 0.f
	else
		displacement = glm::normalize(displacement);
	displacement = displacement * (float)x + displacement * (float)y;
	
	simulation->settings->view->eye += displacement;
}
