#include <iostream>
#include "communication.h"
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) {
	pob_init;

	std::cout << "No1 program" << std::endl;
	HelloWorld::Nothing n(1,1);
//	create_unit<HelloWorld>(&n, std::make_pair(1,1));
//	n.doNothing();
	std::cout << "End No1 program" << std::endl;
	std::cout << "No1 program" << std::endl;
	//return 1;
	HelloWorld::Nothing n2(1,1);
//	create_unit<HelloWorld>(&n2, std::make_pair(1,1));
//	n.doNothing();
	std::cout << "End No1 program" << std::endl;
	MPI_Finalize();
	return 0;
}


