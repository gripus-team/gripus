#include "RenderMesh.h"

RenderMesh::RenderMesh(MemoryMesh* mesh)
	: mesh(mesh), vao(0), elements(0) {
		this->vbo = new GLuint[mesh->entries.size()*2]; //x2, once for vertex buffer, and once for indices
}
RenderMesh::~RenderMesh() {
	delete mesh;
}

void RenderMesh::initialize() {
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(this->mesh->entries.size()*2, this->vbo);

	glBindVertexArray(this->vao);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

	int vboi = 0;
	for(MemoryMesh::Entry* e : this->mesh->entries) {
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo[vboi]);
		glBufferData(GL_ARRAY_BUFFER, e->vertices_count * sizeof(MemoryMesh::Entry::Vertex), e->vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::Entry::Vertex), (GLvoid*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::Entry::Vertex), (GLvoid*)16);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::Entry::Vertex), (GLvoid*)32);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::Entry::Vertex), (GLvoid*)48);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[vboi+1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, e->faces_count * sizeof(MemoryMesh::Entry::Face), e->faces, GL_STATIC_DRAW);

		this->elements += e->faces_count * sizeof(MemoryMesh::Entry::Face) * 3;

		vboi += 2;
	}
}
void RenderMesh::render(glm::mat4 model) {
	glBindVertexArray(this->vao);

	glDrawElements(GL_TRIANGLES, this->elements , GL_UNSIGNED_INT, 0);
}
void RenderMesh::finalize() {
	glDeleteBuffers(this->mesh->entries.size()*2, this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}