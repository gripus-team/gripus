#include "Projection.h"

#include <string>

Projection::Projection()
	: type(ProjectionType::Parallel), size(1.f, -1.f, -1.f, 1.f, 1.f, -1.f) {

}
Projection::Projection(Projection::ProjectionType type, glm::mat3x2 size)
	: type(type), size(size) {
	
}
Projection::~Projection() {
	//nothing to destroy... like, really
}

sdph(Projection) {
	myElement->SetAttribute("type", (this->type==ProjectionType::Parallel ? "parallel" : "perspective"));
	myElement->SetAttribute("size", IXmlSerializable::serializeMatrix3x2(this->size).c_str());
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
}