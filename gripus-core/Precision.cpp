#include "Precision.h"


Precision::Precision()
	: delta(1.0f) {
		
}
Precision::Precision(float delta)
	: delta(delta) {
		
}
Precision::~Precision() {
	//nothing to destroy
}

sdph(Precision) {
	myElement->SetAttribute("delta", std::to_string(this->delta).c_str());
}
dsdph(Precision) {
	const char* str;
	this->delta = (str = myElement->Attribute("delta")) != nullptr ? std::stof(str) : 1.0f;
}