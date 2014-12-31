#pragma once

#include "IXmlSerializable.h"

class Time : public IXmlSerializable {
public:
	Time();
	Time(float step, float start, float end);
	virtual ~Time();

	bool isAtEnd();
	float getTime();
	float getEnd();
	float getStep();
	float doStep();

	serialization();
private:
	float step;
	float time;
	float end;
};

