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
#include "RenderMesh.h"

void callback_error(int error, const char* desc);
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_cursor(GLFWwindow * window, double x, double y);
void callback_mouse(GLFWwindow* window, int button, int action, int mods);
void callback_scroll(GLFWwindow* window, double x, double y);

Simulation* simulation;
Output* output;

double lastTime;

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Invalid command line arguments" << std::endl;
		std::cerr << "Usage: gripus-viewer %path_to_simulation %path_to_output" << std::endl;
		std::cerr << std::endl;

		return EXIT_FAILURE;
	}

	simulation = Simulation::load(argv[1]);
	output = new Output(simulation);
	output->load(argv[2]);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, (int)(640 * ratio)/2, (int)640/2);
	glfwSetCursorPosCallback(window, &callback_cursor);
	glfwSetMouseButtonCallback(window, &callback_mouse);
	glfwSetScrollCallback(window, &callback_scroll);

	//glEnable(GL_CULL_FACE); //DON'T FORGET TO CULL 'EM ALL!!!
	//glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);

	/*GLuint vao, vbo[2];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, &vbo[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	float triangle[9] { 0.f, 1.f, -1.f,
		-1.f, 0.f, -1.f,
		1.f, 0.f, -1.f };
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), &triangle[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	float colors[9] {	1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

	MemoryMesh* mmesh = new MemoryMesh(new Mesh("test", "objects/basketball.3DS", glm::mat4(1.f)));
	mmesh->load();
	RenderMesh* rmesh = new RenderMesh(mmesh);
	rmesh->initialize();

	ShaderProgram* program = new ShaderProgram();
	program->vertexShader = Shader::load("shaders/vertex.shader", GL_VERTEX_SHADER);
	program->fragmentShader = Shader::load("shaders/fragment.shader", GL_FRAGMENT_SHADER);

	bool result = true;
	result &= program->vertexShader->compile(std::cerr);
	result &= program->fragmentShader->compile(std::cerr);
	if (!result)
		return EXIT_FAILURE;

	program->bind_location("vertex_position", 0);
	program->bind_location("vertex_color", 2);

	result = program->link(std::cerr);
	if (!result)
		return EXIT_FAILURE;

	std::cerr << glGetAttribLocation(program->getProgram(), "vertex_position") << 
		  ";" << glGetAttribLocation(program->getProgram(), "vertex_color") << std::endl;

	GLint camera = glGetUniformLocation(program->getProgram(), "camera");

	glUseProgram(program->getProgram());
	while (!glfwWindowShouldClose(window)) {
		lastTime = glfwGetTime();

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
		glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(projection * view));

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		rmesh->render(glm::mat4(1.f));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

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
		}
	}

	glm::vec3 displacement;
	displacement = glm::normalize(simulation->settings->view->center - simulation->settings->view->eye) * directions[0];
	displacement += glm::normalize(glm::cross(simulation->settings->view->center - simulation->settings->view->eye, simulation->settings->view->up)) * directions[1];

	displacement *= simulation->settings->view->step * (float)delta;

	simulation->settings->view->eye += displacement;
	simulation->settings->view->center += displacement;
}
void callback_cursor(GLFWwindow * window, double x, double y) {
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
	if (button==GLFW_MOUSE_BUTTON_1)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else if (button==GLFW_MOUSE_BUTTON_2)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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
