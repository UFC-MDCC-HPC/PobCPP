#include <iostream>
#include "communication.h"
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) {
	pob_init;

	std::cout << "No program" << std::endl;
	create_unit<HelloWorld>();
	std::cout << "End No program" << std::endl;
	MPI_Finalize();
	return 0;
}

