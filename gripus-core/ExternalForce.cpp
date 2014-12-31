#include "ExternalForce.h"

#include <cfloat>

ExternalForce::ExternalForce()
	: object(""), force(0.f, 0.f, 0.f), startTime(0.0f), endTime(+FP_INFINITE) {
		
}
ExternalForce::ExternalForce(std::string object, glm::vec3 force, float startTime, float endTime)
	: object(object), force(force), startTime(startTime), endTime(endTime) {
		
}
ExternalForce::~ExternalForce() {
	//nothing to destroy
}

sdph(ExternalForce) {
	myElement->SetAttribute("object", this->object.c_str());
	myElement->SetAttribute("force", IXmlSerializable::serializeVector(this->force).c_str());
	myElement->SetAttribute("startTime", std::to_string(this->startTime).c_str());
	myElement->SetAttribute("endTime", std::to_string(this->endTime).c_str());
}
dsdph(ExternalForce) {
	const char* str = myElement->Attribute("object");
	if (str)
		this->object = std::string(str);

	str = myElement->Attribute("force");
	if (str)
		this->force = IXmlSerializable::deserializeVector(str);

	str = myElement->Attribute("startTime");
	if (str)
		this->startTime = std::stof(str);

	str = myElement->Attribute("endTime");
	if (str)
		this->endTime = std::stof(str);
}