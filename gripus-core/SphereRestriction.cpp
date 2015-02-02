/*
 * SphereRestriction.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: lexected
 */

#include "SphereRestriction.h"
#include "Constants.h"

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
using namespace glm;

SphereRestriction::SphereRestriction()
	: IRestriction(), radius(0.0f) {
		
}
SphereRestriction::SphereRestriction(glm::vec3 position, IRestriction::Way way, float radius)
	: IRestriction(position, way), radius(radius) {
		
}
SphereRestriction::~SphereRestriction() {
	
}

glm::vec3 SphereRestriction::apply(glm::vec3 & position, glm::vec3 displacement) {
	glm::vec3 distance = position - this->position;
	float distance_length = glm::length(distance);
	
	if((way==Way::In || way==Way::InOut) && distance_length >= this->radius && glm::length(distance+displacement) <= this->radius) {
		distance = glm::normalize(distance)*this->radius/Constants::RadiusImprecision;
		distance_length = this->radius/Constants::RadiusImprecision;
		position = this->position + distance;
		
		glm::vec3 components = glm::polar(distance);
		displacement = rotateY(displacement, (float)M_PI_2-components[1]);
		displacement = rotate(displacement, (float)M_PI_2-components[0], glm::normalize(glm::cross(displacement, glm::vec3(0.0f, 1.0f, 0.0f))));
		displacement[1] = 0.0f;
		
		glm::vec3 new_position = glm::normalize(distance + displacement) * distance_length;
		return (new_position - distance); //=the new displacement
	} else if((way==Way::Out || way==Way::InOut) && distance_length <= this->radius && glm::length(distance+displacement) >= this->radius) {
		distance = glm::normalize(distance)*this->radius*Constants::RadiusImprecision;
		distance_length = this->radius*Constants::RadiusImprecision;
		position = this->position + distance;
		
		/*glm::vec3 components = glm::polar(distance);
		displacement = rotateY(displacement, (float)M_PI_2-components[1]);
		displacement = rotate(displacement, (float)M_PI_2-components[0], glm::normalize(glm::cross(displacement, glm::vec3(0.0f, 1.0f, 0.0f))));
		displacement[1] = 0.0f;*/
		
		glm::vec3 new_position = glm::normalize(distance + displacement) * distance_length;
		return (new_position - distance); //=the new displacement
	} else
		return displacement;
}

sdph(SphereRestriction) {
	myElement->SetAttribute("type", "sphere");
	myElement->SetAttribute("position", IXmlSerializable::serializeVector(position).c_str());
	myElement->SetAttribute("way", IRestriction::serializeWay(this->way).c_str());
	myElement->SetAttribute("radius", std::to_string(this->radius).c_str());
}
dsdph(SphereRestriction) {
	const char* str = myElement->Attribute("position");
	if(str)
		this->position = IXmlSerializable::deserializeVector(str);
	
	str = myElement->Attribute("way");
	if(str)
		this->way = IRestriction::deserializeWay(str);
	
	str = myElement->Attribute("radius");
	if(str)
		this->radius = std::stof(str);
}
