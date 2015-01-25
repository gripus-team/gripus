#include "Environment.h"
#include "Constants.h"

Environment::Environment()
	: gravitations() {
		
}
Environment::Environment(std::vector<IGravitation*> gravitations)
	: gravitations(gravitations) {
		
}
Environment::~Environment() {

}

glm::vec3 Environment::getForce(Object* obj) {
	glm::vec3 resultant_force(0.0f, 0.0f, 0.0f);
	for (IGravitation* gravitation : this->gravitations)
		resultant_force += gravitation->getForce(obj->mass, obj->position + obj->centerOfMass);

	return resultant_force;
}

sdph(Environment) {
	for (IGravitation* gravitation : this->gravitations) {
		TiXmlElement gelem("gravitation");
		gravitation->serialize(&gelem);
		myElement->InsertEndChild(gelem);
	}
}
dsdph(Environment) {
	TiXmlElement* gelem = myElement->FirstChildElement("gravitation");
	while (gelem) {
		IGravitation* gravitation = IGravitation::getGravitation(gelem);
		gravitation->deserialize(gelem);
		this->gravitations.push_back(gravitation);

		gelem = myElement->NextSiblingElement("gravitation");
	}
}
