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
	create_unit<HelloWorld>(&h);
	h.sendHello();
	std::cout << "End Hello program" << std::endl;
	std::cout << "Hello program" << std::endl;
	//return 1;
	HelloWorld::Hello h2;
	create_unit<HelloWorld>(&h2);
	h2.sendHello();
	std::cout << "End Hello program" << std::endl;
	MPI_Finalize();
	return 0;
}
