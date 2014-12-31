#include "PointGravitation.h"


PointGravitation::PointGravitation()
	: position(0.0f, 0.0f, 0.0f), acceleration(0.0f) {
		
}
PointGravitation::PointGravitation(glm::vec3 position, float acceleration)
	: position(position), acceleration(acceleration) {
		
}
PointGravitation::~PointGravitation() {
}

glm::vec3 PointGravitation::getForce(float mass, glm::vec3 position) {
	glm::vec3 accdirection = position - this->position;
	
	if (accdirection == glm::vec3(0.f, 0.f, 0.f)) //we cannot normalize a null vector, that'd be really stupid
		return glm::vec3(0.f, 0.f, 0.f);
	else
		accdirection = glm::normalize(accdirection) * mass * -acceleration;

	return accdirection;
}

sdph(PointGravitation) {
	myElement->SetAttribute("type", "point");
	myElement->SetAttribute("position", IXmlSerializable::serializeVector(this->position).c_str());
	myElement->SetAttribute("acceleration", std::to_string(this->acceleration).c_str());
}
dsdph(PointGravitation) {
	const char* str = myElement->Attribute("position");
	if (str)
		this->position = IXmlSerializable::deserializeVector(std::string(str));

	str = myElement->Attribute("acceleration");
	if (str)
		this->acceleration = std::stof(str);
}