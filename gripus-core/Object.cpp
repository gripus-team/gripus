#include "Object.h"
#include <glm\glm.hpp>

using namespace glm;

Object::Object()
	: id(""), mesh(), mass(0.0), position(0.0, 0.0, 0.0), centerOfMass(0.0, 0.0, 0.0), velocity(0.0, 0.0, 0.0) {
		
}
Object::Object(std::string id, std::string mesh, float mass, glm::vec3 position, glm::vec3 centerOfMass, glm::vec3 velocity)
	: id(id), mesh(mesh), mass(mass), position(position), centerOfMass(centerOfMass), velocity(velocity) {
		
}
Object::Object(Object* object)
	: id(object->id), mesh(object->mesh), mass(object->mass), position(object->position), centerOfMass(object->centerOfMass), velocity(object->velocity) {
		
}
Object::~Object() {
	//so far, there's nothing to destroy... (that's why it's virtual)
}

sdph(Object) {
	myElement->SetAttribute("id", this->id.c_str());
	myElement->SetAttribute("mesh", this->mesh.c_str());
	myElement->SetAttribute("mass", std::to_string(this->mass).c_str());
	myElement->SetAttribute("position", IXmlSerializable::serializeVector(position).c_str());
	myElement->SetAttribute("centerOfMass", IXmlSerializable::serializeVector(centerOfMass).c_str());
	myElement->SetAttribute("velocity", IXmlSerializable::serializeVector(velocity).c_str());
}
dsdph(Object) {
	const char* a = myElement->Attribute("id");
	if (a)
		this->id = std::string(a);

	a = myElement->Attribute("mesh");
	if (a)
		this->mesh = std::string(a);

	a = myElement->Attribute("mass");
	if (a)
		this->mass = std::stof(a);
	
	a = myElement->Attribute("position");
	if (a)
		this->position = IXmlSerializable::deserializeVector(a);

	a = myElement->Attribute("centerOfMass");
	if (a)
		this->centerOfMass = IXmlSerializable::deserializeVector(a);

	a = myElement->Attribute("velocity");
	if (a)
		this->velocity = IXmlSerializable::deserializeVector(a);
}