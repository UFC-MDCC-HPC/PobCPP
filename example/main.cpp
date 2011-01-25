#include "communication.h"
#include <iostream>
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) { 
	for(int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;
	pob_init;
	for(int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;

	std::cout << "Hello program" << std::endl;
	HelloWorld::Hello h;
//	create_unit<HelloWorld>(&h);
	h.sendHello();
	std::cout << "End Hello program" << std::endl;
	MPI_Finalize();
	std::cout << "Hello returning 0" << std::endl;
	return 0;
}
