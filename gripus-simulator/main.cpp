#include <iostream>

using namespace std;

#include <Simulation.h>
#include <Output.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		cerr << "Invalid command line arguments" << endl;
		cerr << "Usage: gripus-simulator %simulation_configuration_path %simulation_output_path" << endl;
		cerr << endl;
	
		return EXIT_FAILURE;
	}

	Simulation* sim = Simulation::load(argv[1]);
	Output* output = new Output(sim);
	
	output->initialize();
	output->write(); //intial snapshot
	while (!sim->settings->time->isAtEnd()) {
		sim->settings->time->doStep();

		sim->simulate_step();
		output->write();
	}
	output->save(argv[2]);

	delete output;
	delete sim;

	return EXIT_SUCCESS;
}