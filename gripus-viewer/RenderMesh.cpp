#include "RenderMesh.h"
#include "ShaderProgramFond.h"
#include "TexturePool.h"

#include <cstdio>
#include <iostream> //KILL THE NOOB WHO PUT THIS HERE!!!!!!!!!!!!

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

RenderMesh::RenderMesh(MemoryMesh* mesh)
	: mesh(mesh), entries() {
		
}
RenderMesh::~RenderMesh() {
	for(RenderEntry* entry : entries)
		delete entry;
}

MemoryMesh* RenderMesh::getMemoryMesh() {
	return this->mesh;
}

void RenderMesh::initialize() {
	for(MemoryMesh::MemoryEntry* me : this->mesh->entries) {
		RenderEntry* re = new RenderEntry();

		glGenVertexArrays(1, &re->vao);
		glGenBuffers(1, &re->vbo);
		glGenBuffers(1, &re->ibo);

		glBindVertexArray(re->vao);
		glEnableVertexAttribArray(0);
    	glEnableVertexAttribArray(1);
    	glEnableVertexAttribArray(2);
    	glEnableVertexAttribArray(3);

    	glBindBuffer(GL_ARRAY_BUFFER, re->vbo);
    	glBufferData(GL_ARRAY_BUFFER, me->vertices_count * sizeof(MemoryMesh::MemoryEntry::Vertex), me->vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::MemoryEntry::Vertex), (GLvoid*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::MemoryEntry::Vertex), (GLvoid*)16);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::MemoryEntry::Vertex), (GLvoid*)32);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MemoryMesh::MemoryEntry::Vertex), (GLvoid*)48);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, re->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, me->faces_count * sizeof(MemoryMesh::MemoryEntry::Face), me->faces, GL_STATIC_DRAW);
		re->elements = me->faces_count * 3;

		if((re->hasTexture = me->hasTexture)) {
			re->texture = TexturePool::getTexture(this->mesh->textures[me->textureIndex]);
		}

		this->entries.push_back(re);
	}
}
void RenderMesh::render(GLuint texUniformLocation) {
	for(RenderEntry* re : this->entries) {
		glBindVertexArray(re->vao);

		if(re->hasTexture) {
			unsigned int slot = TexturePool::getSlot(re->texture);
			glActiveTexture(GL_TEXTURE0 + slot);
			glUniform1i(texUniformLocation, slot);
		}

		glDrawElements(GL_TRIANGLES, re->elements, GL_UNSIGNED_INT, 0);
	}
}
void RenderMesh::finalize() {
	for(RenderEntry* re : this->entries) {
		glDeleteVertexArrays(1, &re->vao);
		glDeleteBuffers(1, &re->vbo);
		glDeleteBuffers(1, &re->ibo);
		
		if(re->hasTexture) {
			//piss on the textures, they will be deallocated by the pool
		}
	}
}