#include <iostream>
#include "communication.h"
#include "create_unit.h"

#include "pobexample.h"
int main(int argc, char** argv) {
	pob_init;

	HelloWorld::World w;
	create_unit<HelloWorld, HelloWorld::World>(&w);
	std::cout << w.recvHello() << std::endl;
	return 0;
}
