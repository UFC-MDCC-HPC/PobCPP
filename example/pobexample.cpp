#include "pobexample.h"
#include "basic_communicator.h"

HelloWorld::Hello::Hello() {
	create_unit<class HelloWorld, class HelloWorld::Hello>(this);
}


HelloWorld::World::World() {
	create_unit<HelloWorld>(this);
}

HelloWorld::Nothing::Nothing(unsigned int i, unsigned int n) : i(i), n(n) {
	create_unit<HelloWorld>(this, std::make_pair(i,n));
}


int HelloWorld::World::recvHello() {
	comm->receive<HelloWorld::Hello, int>(1);
	int data = 0;
	comm->broadcast<Hello>(data);
	std::cout << "Broadcast: " << data << std::endl;
	return data;
}

void HelloWorld::Nothing::doNothing() {
	int data = 0;
	comm->broadcast<Hello>(data);
}
