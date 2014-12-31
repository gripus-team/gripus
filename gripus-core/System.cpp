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

	//first of all (and for now it's also all), calculate the gravitational forces between the objects
	for (Object* o : this->objects) {
		if (o == parent)
			continue;
		
		glm::vec3 distance = (o->position + o->centerOfMass) - (obj->position + obj->centerOfMass);

		// resultant = [unit vec]displacement * G * m1 * m2 / |[vec]displacement|^2
		resultant += glm::normalize(distance)*((Constants::G*obj->mass*o->mass) / (glm::length(distance)*glm::length(distance)));
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