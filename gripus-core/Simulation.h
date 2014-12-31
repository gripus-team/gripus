#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "Settings.h"
#include "Environment.h"
#include "System.h"
#include "ExternalForces.h"
#include "Scene.h"

#include "IXmlSerializable.h"

class Simulation : public IXmlSerializable
{
public:
	Simulation();
	Simulation(Settings* settings, Environment* environment, System* system, ExternalForces* forces, Scene* scene);
	virtual ~Simulation();

	void simulate_step();

	static Simulation* load(std::string simpath);
	static void save(std::string simpath, Simulation* simulation);

	Settings* settings;
	Environment* environment;
	System* system;
	ExternalForces* forces;
	Scene* scene;

	virtual void serialize(TiXmlElement* myElement);
	virtual void deserialize(TiXmlElement* myElement);
private:
	
};

