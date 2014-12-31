#pragma once

#include "IXmlSerializable.h"

class Precision : public IXmlSerializable {
public:
	Precision();
	Precision(float delta);
	virtual ~Precision();

	float delta;

	serialization();
};

