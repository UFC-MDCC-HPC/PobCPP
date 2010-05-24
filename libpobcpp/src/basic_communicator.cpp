#include "basic_communicator.h"
#include "communication.h"

#include <iostream>

namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : env(0)  { }

Basic_Communicator::~Basic_Communicator() { }

void Basic_Communicator::set_environment(Environment* _env) { 
		env = _env;
}

void Basic_Communicator::set_intracomm(MPI_Comm _comm) {
	comm = _comm;
}

void Basic_Communicator::send(const Unit_Type& _unit_type, int _data, const int _tag) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	if(env && world) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.send(unit_rank, _tag, _data);	
			std::cout << "Sending " << _data << " to "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
}

void Basic_Communicator::send(const Unit_Type& _unit_type, std::string _data, const int _tag) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.send(unit_rank, _tag, _data);	
			std::cout << "Sending " << _data << " to "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
}

int Basic_Communicator::receive(const Unit_Type& _unit_type, int _data_type, const int _tag) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	int data;
	if(env && world) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.recv(unit_rank , _tag, data);
			std::cout << "Received " << data << " from "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
	return data;
}

std::string Basic_Communicator::receive(const Unit_Type& _unit_type, std::string _data_type, const int _tag) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	std::string data;
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			world.recv(unit_rank , _tag, data);
			std::cout << "Received " << data << " from "<< _unit_type << " - " << unit_rank << std::endl;
		}
	}
	return data;
}

}


