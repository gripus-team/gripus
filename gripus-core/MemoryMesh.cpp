/*
 * MemoryMesh.cpp
 *
 *  Created on: Jan 2, 2015
 *      Author: lexected
 */

#include "MemoryMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

using namespace Assimp;

#include <iostream> //should not be here, actually, but I am too lazy to do a normal error output

MemoryMesh::MemoryMesh(Mesh* mesh)
	: mesh(mesh), entries(), textures() {

}
MemoryMesh::~MemoryMesh() {
	for(MemoryEntry* e : this->entries) {
		delete [] e->vertices;
		delete [] e->faces;
		delete e;
	}
}

Mesh* MemoryMesh::getMesh() {
	return this->mesh;
}
void MemoryMesh::load() {
	Importer importer;
	const aiScene* scene = importer.ReadFile(mesh->path, aiProcess_Triangulate);
	if(!scene)
		return;
	
	std::string path_directory;
	auto pos = this->mesh->path.rfind('/');
	if(pos != std::string::npos) {
		if(pos != 0) {
			path_directory = this->mesh->path.substr(0, pos) + "/";
		} else {
			path_directory = "/";
		}
	} else {
		path_directory = "./";
	}

	this->entries.resize(scene->mNumMeshes);
	for(int i = 0;i < scene->mNumMeshes;i++) {
		aiMesh* m = scene->mMeshes[i];

		MemoryEntry* entry = new MemoryEntry();

		entry->vertices_count = m->mNumVertices;
		entry->vertices = new MemoryEntry::Vertex[m->mNumVertices];
		MemoryEntry::Vertex* vrx = entry->vertices;
		for(int v = 0;v < m->mNumVertices;v++, vrx++) {
			vrx->vertex[0] = m->mVertices[v].x;
			vrx->vertex[1] = m->mVertices[v].y;
			vrx->vertex[2] = m->mVertices[v].z;
			vrx->vertex[3] = 1.0f;
			vrx->vertex = mesh->transform * vrx->vertex;

			if(m->HasNormals()) {
				vrx->normal[0] = m->mNormals[v].x;
				vrx->normal[1] = m->mNormals[v].y;
				vrx->normal[2] = m->mNormals[v].z;
				vrx->normal[3] = 1.0f;
				
				//TODO: transform normals
			}

			if(m->HasVertexColors(0)) {
				vrx->color[0] = m->mColors[0][v].r;
				vrx->color[1] = m->mColors[0][v].g;
				vrx->color[2] = m->mColors[0][v].b;
				vrx->color[3] = m->mColors[0][v].a;
			} else {
				/* 1.0f to do the multiplication (color*texture) (alpha*texture) and do no harm */
				vrx->color[0] = 1.0f;
				vrx->color[1] = 1.0f;
				vrx->color[2] = 1.0f;
				vrx->color[3] = 1.0f;
			}

			if(m->HasTextureCoords(0)) {
				vrx->texuv[0] = m->mTextureCoords[0][v].x;
				vrx->texuv[1] = m->mTextureCoords[0][v].y;
				vrx->texuv[2] = m->mTextureCoords[0][v].z;
				vrx->texuv[3] = 1.0f;
			}
		}

		entry->faces_count = m->mNumFaces;
		if(!m->HasFaces()) {
			std::cerr << "Entry of the model does not have any faces, and that is really weird!" << std::endl;
			return;
		}
		
		entry->faces = new MemoryEntry::Face[m->mNumFaces];
		for(int f = 0;f < m->mNumFaces;f++) {
			entry->faces[f] = { m->mFaces[f].mIndices[0], m->mFaces[f].mIndices[1], m->mFaces[f].mIndices[2] /*, 0*/ };
		}
		
		if((entry->hasTexture = (scene->mMaterials[m->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0))) {
			aiMaterial* mat = scene->mMaterials[m->mMaterialIndex];
			unsigned int dtextures = mat->GetTextureCount(aiTextureType_DIFFUSE);
			
			aiString path;
			while(dtextures-- > 0) {
				if(mat->GetTexture(aiTextureType_DIFFUSE, dtextures, &path) == AI_SUCCESS) {
					std::string way = path_directory + std::string(path.C_Str());
					
					decltype(this->textures)::iterator it;
					if((it = std::find(this->textures.begin(), this->textures.end(), way)) == this->textures.end()) {
						entry->textureIndex = this->textures.size();
						this->textures.push_back(way);
					} else {
						entry->textureIndex = std::distance(this->textures.begin(), it);
					}
				} else
					std::cerr << "Failed to load material " << m->mMaterialIndex << std::endl;
				
				dtextures = 0; //there is no support for multiple diffuse textures yet
			}
			
		}
		
		this->entries[i] = entry;
	}
}
