#include "Projection.h"

#include <string>

Projection::Projection()
	: type(ProjectionType::Parallel), size(1.f, -1.f, -1.f, 1.f, 1.f, -1.f), scale(1.0f, 1.0f, 1.0f) {

}
Projection::Projection(Projection::ProjectionType type, glm::mat3x2 size, glm::vec3 scale)
	: type(type), size(size), scale(scale) {
	
}
Projection::~Projection() {
	//nothing to destroy... like, really
}

sdph(Projection) {
	myElement->SetAttribute("type", (this->type==ProjectionType::Parallel ? "parallel" : "perspective"));
	myElement->SetAttribute("size", IXmlSerializable::serializeMatrix3x2(this->size).c_str());
	myElement->SetAttribute("scale", IXmlSerializable::serializeVector(this->scale).c_str());
}
dsdph(Projection) {
	const char* str = myElement->Attribute("type");
	if (str) {
		std::string s = str;
		if (s == "parallel")
			this->type = ProjectionType::Parallel;
		else if (s == "perspective")
			this->type = ProjectionType::Perspective;
	}

	str = myElement->Attribute("size");
	if (str)
		this->size = IXmlSerializable::deserializeMatrix3x2(str);
	
	str = myElement->Attribute("scale");
	if (str)
		this->scale = IXmlSerializable::deserializeVector(str);
}
