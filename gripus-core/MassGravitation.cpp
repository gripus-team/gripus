/*
 * MassGravitation.cpp
 *
 *  Created on: Jan 6, 2015
 *      Author: lexected
 */

#include "MassGravitation.h"
#include "Constants.h"

MassGravitation::MassGravitation()
	: position(0.0f, 0.0f, 0.0f), mass(0.0f) {
		
}
MassGravitation::MassGravitation(glm::vec3 position, float mass)
	: position(position), mass(mass) {
		
}
MassGravitation::~MassGravitation() {
	// DO NOTHIN' JON SNOW!
}

glm::vec3 MassGravitation::getForce(float mass, glm::vec3 position) {
	glm::vec3 displacement = position - this->position;
	return -glm::normalize(displacement) * (Constants::G * this->mass * mass / (glm::length(displacement) * glm::length(displacement)));
}

sdph(MassGravitation) {
	myElement->SetAttribute("type", "mass");
	myElement->SetAttribute("position", IXmlSerializable::serializeVector(this->position).c_str());
	myElement->SetAttribute("mass", std::to_string(this->mass).c_str());
}
dsdph(MassGravitation) {
	const char* str;
	str = myElement->Attribute("position");
	if(str)
		this->position = IXmlSerializable::deserializeVector(str);
	
	str = myElement->Attribute("mass");
	if(str)
		this->mass = std::stof(str);
}
