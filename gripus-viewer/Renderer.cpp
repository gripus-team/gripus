#include "Renderer.h"

Renderer::Renderer(std::vector<RenderMesh*> meshes)
	: meshes(meshes) {

}
Renderer::~Renderer() {
	for(RenderMesh* mm : this->meshes) {
		delete mm;
	}
}

void Renderer::initialize() {

}
void Renderer::render() {
	
}
void Renderer::finalize() {
	
}
