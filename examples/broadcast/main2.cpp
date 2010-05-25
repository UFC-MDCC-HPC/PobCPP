#include "communication.h"
#include <iostream>
#include "bcast.h"
#include "create_unit.h"

int main(int argc, char** argv) { 

	std::cout << "Example program" << std::endl;
	Bcast_Example::Example h;
	create_unit<Bcast_Example>(&h);
	h.doBcast();
	std::cout << "End Example program" << std::endl;
	MPI_Finalize();
	return 0;
}
