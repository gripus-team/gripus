#include "ExternalForces.h"
#include "Time.h"

ExternalForces::ExternalForces()
	: forces() {
		
}
ExternalForces::ExternalForces(std::vector<ExternalForce*> forces)
	: forces(forces) {
		
}
ExternalForces::~ExternalForces() {
	//nothing to destroy
}

glm::vec3 ExternalForces::getForce(Object* object, Time* t) {
	if (t == nullptr)
		t = new Time(0.f, 0.f, +FP_INFINITE);

	glm::vec3 resultant(0.0f, 0.0f, 0.0f);
	for (ExternalForce* ef : this->forces) {
		if (ef->object == object->id  && ef->startTime <= t->getTime() && t->getTime() < ef->endTime)
			resultant += ef->force;
	}

	return resultant;
}

sdph(ExternalForces) {
	for (ExternalForce* f : this->forces) {
		TiXmlElement e("force");
		f->serialize(&e);
		myElement->InsertEndChild(e);
	}
}
dsdph(ExternalForces) {
	TiXmlElement* e = myElement->FirstChildElement("force");
	while (e) {
		ExternalForce* ef = new ExternalForce();
		ef->deserialize(e);
		this->forces.push_back(ef);

		e = e->NextSiblingElement("force");
	}
}