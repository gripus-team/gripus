#include "System.h"
#include "Constants.h"

System::System()
	: objects() {
		
}
System::System(std::vector<Object*> objects)
	: objects(objects) {
	
}
System::~System() {
	for (Object* obj : this->objects)
		delete obj;
}

glm::vec3 System::getForce(Object* obj, Object* parent) {
	if (parent == nullptr)
		parent = obj;

	glm::vec3 resultant(0.0f, 0.0f, 0.0f);
	
	for (Object* o : this->objects) {
		if (o == parent)
			continue;

		glm::vec3 distance;
		if(obj->mass != 0.f && o->mass != 0.f) {
			// first of all, get the net gravitational force
			distance = (o->position + o->centerOfMass) - (obj->position + obj->centerOfMass);
			// resultant = [unit vec]distance * G * m1 * m2 / |[vec]distance|^2
			resultant += glm::normalize(distance)*((Constants::G*obj->mass*o->mass) / (glm::length(distance)*glm::length(distance)));
		}
		
		if(obj->charge != 0.f && o->charge != 0.f) {
			//then, calculate the net force due to electric charge
			distance = o->position - obj->position;
			// resultant = [unit vec]distance * q1 * q2 / (4 * pi * permittivity * |[vec]distance|^2)
			resultant += glm::normalize(distance)*((obj->charge * o->charge) / (4 * Constants::Pi * Constants::Epsilon0 * glm::length(distance) * glm::length(distance)));
		}
	}

	return resultant;
}

sdph(System) {
	for (Object* obj : this->objects) {
		TiXmlElement e("object");
		obj->serialize(&e);

		myElement->InsertEndChild(e);
	}
}
dsdph(System) {
	TiXmlElement* e = myElement->FirstChildElement("object");
	while (e) {
		Object* obj = new Object();
		obj->deserialize(e);
		this->objects.push_back(obj);

		e = e->NextSiblingElement("object");
	}
}
