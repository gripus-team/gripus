#include "Scene.h"


Scene::Scene()
	: meshes() {
		
}
Scene::Scene(std::vector<Mesh*> meshes)
	: meshes(meshes) {
		
}
Scene::~Scene() {
	//there actually is something to destroy, for this time...
	for (Mesh* m : meshes)
		delete m;
}

sdph(Scene) {
	for (Mesh* m : this->meshes) {
		TiXmlElement e("mesh");
		m->serialize(&e);
		myElement->InsertEndChild(e);
	}
}
dsdph(Scene) {
	TiXmlElement* e = myElement->FirstChildElement("mesh");
	while (e) {
		Mesh* nm = new Mesh();
		nm->deserialize(e);
		this->meshes.push_back(nm);

		e = e->NextSiblingElement("mesh");
	}
}