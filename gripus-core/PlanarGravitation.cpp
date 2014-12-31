#include "PlanarGravitation.h"


PlanarGravitation::PlanarGravitation()
: position(0.0f, 0.0f, 0.0f), acceleration(0.0f, 0.0f, 0.0f) {
		
}
PlanarGravitation::PlanarGravitation(glm::vec3 position, glm::vec3 acceleration)
: position(position), acceleration(acceleration) {
		
}
PlanarGravitation::~PlanarGravitation() {
		
}

const float MAX_SECANT = ((float)1.41421356237);
glm::vec3 PlanarGravitation::getForce(float mass, glm::vec3 position) {
	glm::vec3 force = position - this->position;
	if (force != glm::vec3(0.0f, 0.0f, 0.0f) && acceleration != glm::vec3(0.0f, 0.0f, 0.0f)) {
		force = glm::normalize(force) - glm::normalize(acceleration);

		if (glm::length(force) == MAX_SECANT)
			force = glm::vec3(0.0f, 0.0f, 0.0f);
		else if (glm::length(force) < MAX_SECANT)
			force = -this->acceleration;
		else
			force = this->acceleration;
	} else {
		force = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	force *= mass;

	return force;
}

sdph(PlanarGravitation) {
	myElement->SetAttribute("type", "planar");
	myElement->SetAttribute("position", IXmlSerializable::serializeVector(this->position).c_str());
	myElement->SetAttribute("acceleration", IXmlSerializable::serializeVector(this->acceleration).c_str());
}
dsdph(PlanarGravitation) {
	const char* str = myElement->Attribute("position");
	if (str)
		this->position = IXmlSerializable::deserializeVector(std::string(str));

	str = myElement->Attribute("acceleration");
	if (str)
		this->acceleration = IXmlSerializable::deserializeVector(std::string(str));
}