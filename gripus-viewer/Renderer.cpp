#include "Renderer.h"
#include "TexturePool.h"

#include <MemoryMesh.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::vector<Renderer::RenderPair> Renderer::pairs;

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
}
void Renderer::render(GLuint modelUniformLocation, GLuint texUniformLocation) {
	for(RenderPair & p : pairs) {
		glm::mat4 model  = glm::translate(glm::mat4(1.f), p.object->position)
						 * glm::rotate(glm::mat4(1.f), p.object->orientation.x, glm::vec3(1.0f, 0.0f, 0.0f))
						 * glm::rotate(glm::mat4(1.f), p.object->orientation.y, glm::vec3(0.0f, 1.0f, 0.0f))
						 * glm::rotate(glm::mat4(1.f), p.object->orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

		p.mesh->render(texUniformLocation);
	}
}
void Renderer::finalize() {
	for(RenderPair & p : pairs) {
		p.mesh->finalize();
		delete p.mesh;
	}

	TexturePool::finalize();
}