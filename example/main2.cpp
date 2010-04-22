#include <iostream>
#include "communication.h"
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) {
	pob_init;

	std::cout << "World program" << std::endl;
	HelloWorld::World w;
	create_unit<HelloWorld>(&w);
	std::cout << w.recvHello() << std::endl;
	return 0;
}
