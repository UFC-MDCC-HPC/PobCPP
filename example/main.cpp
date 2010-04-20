#include "communication.h"
#include <iostream>
#include "create_unit.h"

#include "pobexample.h"

int main(int argc, char** argv) { 
	pob_init;
	HelloWorld::Hello h;
	create_unit<HelloWorld, HelloWorld::Hello>(&h);
	h.sendHello();
	return 0;
}
