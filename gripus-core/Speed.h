#pragma once

#include "IXmlSerializable.h"


class Speed : public IXmlSerializable {
public:
	Speed();
	Speed(float boost);
	virtual ~Speed();

	float boost;

	serialization();
};

