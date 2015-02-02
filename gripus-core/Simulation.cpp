#include "Simulation.h"
#include "Environment.h"
#include "Object.h"
#include "Scene.h"

#include <tinyxml.h>

#include <string>
#include <cfloat>

Simulation::Simulation()
: settings(new Settings()), environment(new Environment()), system(new System()), forces(new ExternalForces()), scene(new Scene()) {
		
}
Simulation::Simulation(Settings* settings, Environment* environment, System* system, ExternalForces* forces, Scene* scene)
	: settings(settings), environment(environment), system(system), forces(forces), scene(scene) {
		
}
Simulation::~Simulation() {
	delete settings;
	delete environment;
	delete system;
}

void Simulation::simulate_step() {
	for (Object* obj : this->system->objects) {
		//calculate all of the forces which act on an object
		// 1. environmental
		// 2. systemic (objects acting one on another)
		// 3. external (applied forces)
		// 4. more to come...
		glm::vec3 resultant = this->environment->getForce(obj) + this->system->getForce(obj) + this->forces->getForce(obj, this->settings->time);
		
		obj->velocity += resultant * this->settings->time->getStep() / obj->mass;
	
		glm::vec3 displacement = obj->velocity * this->settings->time->getStep();	
		for(IRestriction* res : system->restrictions)
			displacement = res->apply(obj->position, displacement);
		obj->velocity = displacement / this->settings->time->getStep();
	}
	
	//repositioning must be separated from the revaluation loop
	for(Object* obj : this->system->objects) {
		obj->position += obj->velocity * this->settings->time->getStep();
		
		//don't forget to rotate it, of course
		obj->orientation += obj->rotation * this->settings->time->getStep();
	}
}

Simulation* Simulation::load(std::string simpath) {
	Simulation* ret = new Simulation();

	TiXmlDocument document;
	if (document.LoadFile(simpath.c_str())) {
		ret->deserialize(document.RootElement());
	}

	return ret;
}
void Simulation::save(std::string simpath, Simulation* simulation) {
	TiXmlDocument doc;
	TiXmlElement element("simulation");
	doc.InsertEndChild(element);

	simulation->serialize(&element);
	
	doc.SaveFile(simpath.c_str());
}

void Simulation::serialize(TiXmlElement* myElement) {
	TiXmlElement setelem("settings");
	this->settings->serialize(&setelem);
	TiXmlElement envelem("environment");
	
	TiXmlElement syselem("system");
	this->system->serialize(&syselem);

	TiXmlElement fcselem("forces");
	this->forces->serialize(&fcselem);

	TiXmlElement sceelem("scene");
	this->scene->serialize(&sceelem);

	myElement->InsertEndChild(setelem);
	myElement->InsertEndChild(envelem);
	myElement->InsertEndChild(syselem);
	myElement->InsertEndChild(fcselem);
	myElement->InsertEndChild(sceelem);
}
void Simulation::deserialize(TiXmlElement* myElement) {
	TiXmlElement* e = myElement->FirstChildElement("settings");
	if (e)
		this->settings->deserialize(e);
	
	e = myElement->FirstChildElement("environment");
	if (e)
		this->environment->deserialize(e);

	e = myElement->FirstChildElement("system");
	if (e)
		this->system->deserialize(e);

	e = myElement->FirstChildElement("forces");
	if (e)
		this->forces->deserialize(e);

	e = myElement->FirstChildElement("scene");
	if (e)
		this->scene->deserialize(e);
}
