#include "View.h"


View::View()
	: eye(0.0f, 0.0f, 1.0f), center(0.f, 0.f, 0.f), up(0.0f, 1.0f, 0.0f), step(1.0f) {
		
}
View::View(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float step)
	: eye(eye), center(center), up(up), step(step) {
		
}
View::~View() {
	//there's nothinh to destroy
}

sdph(View) {
	myElement->SetAttribute("eye", IXmlSerializable::serializeVector(this->eye).c_str());
	myElement->SetAttribute("center", IXmlSerializable::serializeVector(this->center).c_str());
	myElement->SetAttribute("up", IXmlSerializable::serializeVector(this->up).c_str());
	myElement->SetAttribute("step", std::to_string(this->step).c_str());
}
dsdph(View) {
	const char* str = myElement->Attribute("eye");
	if (str)
		this->eye = IXmlSerializable::deserializeVector(str);

	str = myElement->Attribute("center");
	if (str)
		this->center = glm::normalize(IXmlSerializable::deserializeVector(str));

	str = myElement->Attribute("up");
	if (str)
		this->up = glm::normalize(IXmlSerializable::deserializeVector(str));

	str = myElement->Attribute("step");
	if (str)
		this->step = std::stof(str);
}