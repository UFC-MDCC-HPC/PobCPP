#include <iostream>
#include "communication.h"
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) {
	pob_init;

	std::cout << "World program" << std::endl;
	HelloWorld::World w;
//	create_unit<HelloWorld>(&w);
	std::cout << w.recvHello() << std::endl;
	std::cout << "End World program" << std::endl;
//	return 1;
	HelloWorld::World w2;
//	create_unit<HelloWorld>(&w2);
	std::cout << w2.recvHello() << std::endl;
	std::cout << "End World program" << std::endl;
	MPI_Finalize();
	return 0;
}
