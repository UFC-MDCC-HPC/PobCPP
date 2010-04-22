#include "basic_communicator.h"
#include "communication.h"

#include <iostream>

namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : env(0)  { }

Basic_Communicator::~Basic_Communicator() { }

void Basic_Communicator::set_environment(Environment* _env) { 
		env = _env;
}

void Basic_Communicator::send(const Unit_Type& _unit_type, int _data, const int _tag) {
	boost::mpi::communicator world; // FIXME Should be a intracommunicator. Only between units.
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.send(unit_rank, _tag, _data);	
			std::cout << "Sending " << _data << " to "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
}

int Basic_Communicator::receive(const Unit_Type& _unit_type, int _data_type, const int _tag) {
	boost::mpi::communicator world; // FIXME Should be a intracommunicator. Only between units.
	int data;
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.recv(unit_rank , _tag, data);
			std::cout << "Receiving " << data << " from "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
	return data;
}

}


