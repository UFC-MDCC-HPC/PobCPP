#include "communication.h"
#include <iostream>
#include "bcast.h"
#include "create_unit.h"

int main(int argc, char** argv) { 

	std::cout << "Receiver program" << std::endl;
	Bcast_Example::Receiver r;
	create_unit<Bcast_Example>(&r);
	r.doBcast();
	std::cout << "End Receiver program" << std::endl;
	MPI_Finalize();
	return 0;
}
