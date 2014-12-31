#pragma once

#include <IXmlSerializable.h>
#include <Settings.h>
#include <tinyxml.h>

class Simulation : public IXmlSerializable {
public:
	Simulation();
	virtual ~Simulation();

	Settings* settings;

	serialization();
};

