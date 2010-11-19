#include "pobexample.h"
#include "basic_communicator.h"

void HelloWorld::Hello::sendHello() {
	comm->send<HelloWorld::World>(42, 1);
}

int HelloWorld::World::recvHello() {
	comm->receive<HelloWorld::Hello, int>(1);
	comm->receive<HelloWorld::Nothing, int>(0,2);
}

void HelloWorld::Nothing::doNothing() {
	comm->send<HelloWorld::World>(43,2);
}
