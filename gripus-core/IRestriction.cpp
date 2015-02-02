/*
 * Restriction.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: lexected
 */

#include "IRestriction.h"
#include "SphereRestriction.h"

IRestriction::IRestriction()
	: position(0.0f), way(IRestriction::Way::InOut){
	
}
IRestriction::IRestriction(glm::vec3 position, IRestriction::Way way)
	: position(position), way(way) {
		
}
IRestriction::~IRestriction() {
	//delete nothin', jon snow
}

std::string IRestriction::serializeWay(IRestriction::Way way) {
	switch(way) {
	case Way::In:
		return "in";
		break;
	case Way::Out:
		return "out";
		break;
	case Way::InOut:
		return "inout";
		break;
	default:
		return "";
		break;
	}
}
IRestriction::Way IRestriction::deserializeWay(std::string str) {
	if(str=="in")
		return Way::In;
	else if(str=="out")
		return Way::Out;
	else
		return Way::InOut;
}

IRestriction* IRestriction::getRestriction(TiXmlElement* element) {
	std::string str(element->Attribute("type"));
	if(str=="sphere")
		return new SphereRestriction();
	else
		return new SphereRestriction();
}
