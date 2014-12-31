#include "Output.h"


Output::Output(Simulation* simulation)
	: simulation(simulation), output(nullptr) {
		
}
Output::~Output() {
	delete this->output;
}

void Output::initialize() {
	this->output = new TiXmlDocument();

	TiXmlElement root("output");
	root.SetAttribute("time", "time_will_be_added_in_future"); //TODO: add current time, asctime and ctime won't work (others are just windows specific)

	TiXmlElement settings("settings");
	simulation->settings->serialize(&settings);
	root.InsertEndChild(settings);

	TiXmlElement states("states");
	root.InsertEndChild(states);

	this->output->InsertEndChild(root);
	
	this->states = this->output->FirstChildElement("output")->FirstChildElement("states");
}
void Output::load(const char* fpath) {
	this->output = new TiXmlDocument();
	this->output->LoadFile(fpath);

	this->states = this->output->FirstChildElement("output")->FirstChildElement("states");
	if (states == nullptr) {
		this->output = new TiXmlDocument();
		this->initialize();
	}
}

void Output::read() {
	static TiXmlNode* current = nullptr;

	TiXmlElement* element = nullptr;
	while ((current = output->IterateChildren(current)) != nullptr && (element = dynamic_cast<TiXmlElement*>(current)) == nullptr)
		;

	if (element == nullptr)
		return;

	this->simulation->settings->time->doStep(); // move the state to time...
	this->simulation->system->deserialize(element);
}
void Output::write() {
	TiXmlElement state("state");
	state.SetAttribute("time", std::to_string(simulation->settings->time->getTime()).c_str());

	simulation->system->serialize(&state);

	this->states->InsertEndChild(state);
}

void Output::save(const char* fpath) {
	this->output->SaveFile(fpath);
}
void Output::finalize() {
	this->states = nullptr;
}
