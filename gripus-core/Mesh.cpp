#include "Mesh.h"


Mesh::Mesh()
	: name(), path(), transform(1.f) {
		
}
Mesh::Mesh(std::string name, std::string path, glm::mat4 transform)
	: name(name), path(path), transform(transform) {
		
}
Mesh::~Mesh() {
	//nothing to destroy...
}

sdph(Mesh) {
	myElement->SetAttribute("name", this->name.c_str());
	myElement->SetAttribute("path", this->path.c_str());
	myElement->SetAttribute("transform", IXmlSerializable::serializeMatrix4x4(this->transform).c_str());
}
dsdph(Mesh) {
	const char* s = myElement->Attribute("name");
	if (s)
		this->name = std::string(s);

	s = myElement->Attribute("path");
	if (s)
		this->path = std::string(s);

	s = myElement->Attribute("transform");
	if (s)
		this->transform = IXmlSerializable::deserializeMatrix4x4(s);
}