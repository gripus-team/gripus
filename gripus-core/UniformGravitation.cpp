#include "UniformGravitation.h"

#include "glm\ext.hpp"
using namespace glm;

UniformGravitation::UniformGravitation()
	: IGravitation(), acceleration(0.0, 0.0, 0.0) {
		
}
UniformGravitation::UniformGravitation(glm::vec3 acceleration)
	: IGravitation(), acceleration(acceleration) {
		
}
UniformGravitation::~UniformGravitation() {
	
}

glm::vec3 UniformGravitation::getForce(float mass, glm::vec3 position) {
	return -this->acceleration*mass;
}

sdph(UniformGravitation) {
	myElement->SetAttribute("type", "uniform");
	myElement->SetAttribute("acceleration", IXmlSerializable::serializeVector(acceleration).c_str());
}
dsdph(UniformGravitation) {
	const char* str = myElement->Attribute("acceleration");
	if (str)
		this->acceleration = IXmlSerializable::deserializeVector(str);
}