#include "Time.h"

Time::Time()
	: step(0.0f), time(0.0f), end(0.0f) {
		
}
Time::Time(float step, float start, float end)
	: step(step), time(start), end(end) {
		
}
Time::~Time() {
	//there's nothing to destroy
}

bool Time::isAtEnd() {
	return this->time >= this->end;
}
float Time::getTime() {
	return this->time;
}
float Time::getEnd() {
	return this->end;
}
float Time::getStep() {
	return this->step;
}
float Time::doStep() {
	return (this->time += this->step);
}

sdph(Time) {
	myElement->SetAttribute("step", std::to_string(this->step).c_str());
	myElement->SetAttribute("start", std::to_string(this->time).c_str());
	myElement->SetAttribute("end", std::to_string(this->end).c_str());
}
dsdph(Time) {
	const char* str;
	this->step = std::stof((str = myElement->Attribute("step")) != nullptr ? str : "0.0");
	this->time = std::stof((str = myElement->Attribute("start")) != nullptr ? str : "0.0");
	this->end = std::stof((str = myElement->Attribute("end")) != nullptr ? str : "0.0");
}