#include "pobexample.h"
#include "basic_communicator.h"

HelloWorld::Hello::Hello() {
	create_unit<class HelloWorld>(this);
}


HelloWorld::World::World() {
	create_unit<HelloWorld>(this);
}


int HelloWorld::World::recvHello() {
	comm->receive<HelloWorld::Hello, int>(1);
	int data = 0;
	comm->broadcast<Hello>(data);
	std::cout << "Broadcast: " << data << std::endl;
	return data;
}

