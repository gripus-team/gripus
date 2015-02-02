#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include <Simulation.h>
#include <Output.h>

int main(int argc, char** argv) {
	if (argc != 3 && argc != 4) {
		cerr << "Invalid command line arguments" << endl;
		cerr << "Usage: gripus-simulator %simulation_configuration_path %simulation_output_path" << endl;
		cerr << "       gripus-simulator --end %simulation_configuration_path %simulation_output_path" << endl;
		cerr << endl;
	
		return EXIT_FAILURE;
	}
	
	bool endOnly = false;
	if(string(argv[1])=="--end") {
		endOnly = true;
		argv[1] = argv[2];
		argv[2] = argv[3];
	}

	Simulation* sim = Simulation::load(argv[1]);
	Output* output = new Output(sim);
	
	output->initialize();
	if(!endOnly)
		output->write(); //intial snapshot
	
	time_t last = time(nullptr);
	while (!sim->settings->time->isAtEnd()) {
		sim->settings->time->doStep();
		sim->simulate_step();
		
		if(!endOnly)
			output->write();
		
		if(time(nullptr) - last >= 10) {
			std::cout << "Progress: " << (sim->settings->time->getTime() / sim->settings->time->getEnd() * 100) << "%" << std::endl;
			last = time(nullptr);
		}
	}
	
	if(endOnly)
		output->write();
	output->save(argv[2]);

	delete output;
	delete sim;

	return EXIT_SUCCESS;
}
