#include "Speed.h"

Speed::Speed()
	: boost(1.0f) {
		
}
Speed::Speed(float boost)
	: boost(boost) {
		
}
Speed::~Speed() {
	
}

sdph(Speed) {
	myElement->SetAttribute("boost", std::to_string(this->boost).c_str());
}
dsdph(Speed) {
	const char* str = myElement->Attribute("boost");
	if (str)
		this->boost = std::stof(str);
}