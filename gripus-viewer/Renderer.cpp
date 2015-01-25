#include "Renderer.h"
#include "TexturePool.h"

#include <MemoryMesh.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::vector<Renderer::RenderPair> Renderer::pairs;

GLuint Renderer::velocity_vao;
GLuint Renderer::velocity_vbo;
glm::vec3 Renderer::velocity_data[2][2] = { {{0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}}, {{0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}} };
float Renderer::velocity_boost;

void Renderer::initialize(Simulation* simulation) {
	TexturePool::initialize();

	std::vector<RenderMesh*> rmeshes;
	for(Mesh* m : simulation->scene->meshes) {
		MemoryMesh* mm = new MemoryMesh(m);
		mm->load();
		RenderMesh* rm = new RenderMesh(mm);
		rm->initialize();

		rmeshes.push_back(rm);
	}

	for(Object* obj : simulation->system->objects) {
		RenderPair pair;
		pair.object = obj;
		pair.mesh = nullptr;

		for(int i = 0;i < rmeshes.size();i++) {
			Mesh* m = simulation->scene->meshes[i];

			if(m->name == obj->mesh) {
				pair.mesh = rmeshes[i];
				break;
			}
		}

		if(pair.mesh==nullptr) {
			std::cerr << "Unknown mesh \"" << obj->mesh << "\" found on object \"" << obj->id << "\"" << std::endl;
			break;
		}

		pairs.push_back(pair);
	}

	glGenVertexArrays(1, &velocity_vao);
	glBindVertexArray(velocity_vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(2);
	glGenBuffers(1, &velocity_vbo);

	velocity_boost = simulation->settings->speed->boost;
}
void Renderer::render(GLuint modelUniformLocation, GLuint hasTexUniformLocation, GLuint texUniformLocation, bool showVelocities) {
	for(RenderPair & p : pairs) {
		glm::mat4 model  = glm::translate(glm::mat4(1.f), p.object->position);

		if(showVelocities) {
			glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(velocity_vao);
			glBindBuffer(GL_ARRAY_BUFFER, velocity_vbo);
				velocity_data[1][0] = p.object->velocity * velocity_boost;
				glBufferData(GL_ARRAY_BUFFER, sizeof(velocity_data), velocity_data, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (GLvoid*)0);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (GLvoid*)sizeof(glm::vec3));
			
			glUniform1i(hasTexUniformLocation, 0);
			glDrawArrays(GL_LINES, 0, 2);
			glUniform1i(hasTexUniformLocation, 1);
		}

		model = model
				* glm::rotate(glm::mat4(1.f), p.object->orientation.x, glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(glm::mat4(1.f), p.object->orientation.y, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::rotate(glm::mat4(1.f), p.object->orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		
		p.mesh->render(texUniformLocation);
	}
}
void Renderer::finalize() {
	glDeleteVertexArrays(1, &velocity_vao);
	glDeleteBuffers(1, &velocity_vbo);

	for(RenderPair & p : pairs) {
		p.mesh->finalize();
		delete p.mesh;
	}

	TexturePool::finalize();
}