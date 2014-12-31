#pragma once

#include "IXmlSerializable.h"
#include "Simulation.h"

class Output {
public:
	Output(Simulation* simulation);
	virtual ~Output();

	void load(const char* fpath);
	void initialize();

	void read();
	void write();

	void save(const char* fpath);
	void finalize();

	Simulation* simulation;
private:
	TiXmlDocument* output;
	TiXmlElement* states;
};

