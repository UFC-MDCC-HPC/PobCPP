#ifndef __BASIC_COMMUNICATOR_H__
#define __BASIC_COMMUNICATOR_H__

#include "unit_type.h"
#include "communicator.h"
#include "communication.h"
#include "environment.h"

#include <iostream>

namespace Pobcpp {

class Basic_Communicator : public Communicator<Basic_Communicator> {
public:
	Basic_Communicator(); 
	~Basic_Communicator();

	template<typename Data>
	void sync_send(const Unit_Type& _unit_type, Data _data, const int _tag);

	template<typename Data>
	Data sync_receive(const Unit_Type& _unit_type, const int _tag, Data _data_type);

private:

	boost::mpi::communicator world; // FIXME Should be a intracommunicator. Only between units.
};

template<typename Data>
void Basic_Communicator::sync_send(const Unit_Type& _unit_type, Data _data, const int _tag) {
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			std::cout << "Sync_send to "<< _unit_type << " - " << unit_rank << std::endl;
			world.send(unit_rank, _tag, _data);	
		}
	}
}

template<typename Data>
Data Basic_Communicator::sync_receive(const Unit_Type& _unit_type, const int _tag, Data _data_type) {
	Data data;
	//get rank
	if(env) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			std::cout << "Sync_receive from "<< _unit_type << " - " << unit_rank << std::endl;
			world.recv(unit_rank , _tag, data);
		}
	}
	return data;
}

}

#endif

