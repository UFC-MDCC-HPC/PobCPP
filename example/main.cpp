#include "communication.h"
#include <iostream>
#include "pobexample.h"
#include "create_unit.h"

int main(int argc, char** argv) { 
	pob_init;
	std::cout << "Hello program" << std::endl;
	HelloWorld::Hello h;
	create_unit<HelloWorld>(&h);
	h.sendHello();
	return 0;
}
