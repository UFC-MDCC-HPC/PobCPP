#include "basic_communicator.h"
#include "communication.h"
#include <boost/mpi/collectives.hpp>
#include <iostream>


#define Basic_Communicator_send_impl(datatype) \
void Basic_Communicator::send(const Unit_Type& _unit_type, const datatype& _data, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.send(unit_rank, _tag, _data);	\
			std::cout << "Sending " << _data << " to "<< _unit_type << " - " << unit_rank << std::endl; \
		} \
	} \
} 

#define Basic_Communicator_receive_impl(datatype) \
datatype Basic_Communicator::receive(const Unit_Type& _unit_type, const datatype& _data_type, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	datatype data; \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.recv(unit_rank , _tag, data); \
			std::cout << "Received " << data << " from "<< _unit_type << " - " << unit_rank << std::endl; \
		} \
	} \
	return data; \
} 

#define Basic_Communicator_broadcast_impl(datatype) \
void Basic_Communicator::broadcast(const Unit_Type& _unit_type, datatype& value) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			boost::mpi::broadcast(world, value, unit_rank); \
			std::cout << "Broadcast executed " << " root: "<< _unit_type << " - " << unit_rank << std::endl; \
		} \
	} \
}
#define Basic_Communicator_broadcast_array_impl(datatype) \
void Basic_Communicator::broadcast(const Unit_Type& _unit_type, datatype* values, int n) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			boost::mpi::broadcast(world, values, n, unit_rank); \
			std::cout << "Broadcast executed " << " root: "<< _unit_type << " - " << unit_rank << std::endl; \
		} \
	} \
}

#define Basic_Communicator_gather_impl(datatype) \
void Basic_Communicator::gather(const Unit_Type& _unit_type, const datatype& in_value, datatype* out_values) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			boost::mpi::gather(world, in_value, out_values, unit_rank); \
			std::cout << "Gather executed " << " root: "<< _unit_type << " - " << unit_rank << std::endl; \
		} \
	} \
}
namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : env(0)  { }

Basic_Communicator::~Basic_Communicator() { }

void Basic_Communicator::set_environment(Environment* _env) { 
		env = _env;
}

void Basic_Communicator::set_intracomm(MPI_Comm _comm) {
	comm = _comm;
}

Basic_Communicator_send_impl(int);
Basic_Communicator_send_impl(float);
Basic_Communicator_send_impl(double);
Basic_Communicator_send_impl(std::string);

Basic_Communicator_receive_impl(int);
Basic_Communicator_receive_impl(float);
Basic_Communicator_receive_impl(double);
Basic_Communicator_receive_impl(std::string);

Basic_Communicator_broadcast_impl(int);
Basic_Communicator_broadcast_impl(float);
Basic_Communicator_broadcast_impl(double);
Basic_Communicator_broadcast_impl(std::string);

Basic_Communicator_broadcast_array_impl(int);
Basic_Communicator_broadcast_array_impl(float);
Basic_Communicator_broadcast_array_impl(double);
Basic_Communicator_broadcast_array_impl(std::string);

Basic_Communicator_gather_impl(int);
Basic_Communicator_gather_impl(float);
Basic_Communicator_gather_impl(double);
Basic_Communicator_gather_impl(std::string);
}


