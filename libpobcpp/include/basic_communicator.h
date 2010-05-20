#ifndef __BASIC_COMMUNICATOR_H__
#define __BASIC_COMMUNICATOR_H__

#include "unit_type.h"
#include "communicator.h"
#include "environment.h"
#include <mpi.h>
#include <map> // std::pair

#include <string>

namespace Pobcpp {

class Basic_Communicator {
public:
	Basic_Communicator(); 
	~Basic_Communicator();

	void set_environment(Environment* _env);
	void set_intracomm(MPI_Comm _comm);
	
	template<typename Type, typename Data>
	void send(Data data, const int tag, unsigned int _enumi = 0);

	void send(const Unit_Type& _unit_type, int _data, const int _tag);
	void send(const Unit_Type& _unit_type, std::string _data, const int _tag);

	template<typename Type, typename Data>
	Data receive(const int _tag, unsigned int _enumi = 0);

	int receive(const Unit_Type& _unit_type, int _data_type, const int _tag);
	std::string receive(const Unit_Type& _unit_type, std::string _data_type, const int _tag);

private:

	Environment* env;
	MPI_Comm comm;
};

template<typename Type, typename Data>
void Basic_Communicator::send(Data _data, const int _tag, unsigned int _enumi) {
		Type* un;
		Unit_Type unit_type(un);
		unit_type.set_enums(std::make_pair(_enumi,0));
		send(unit_type, _data, _tag);
}

template<typename Type, typename Data>
Data Basic_Communicator::receive(const int _tag, unsigned int _enumi) {
	Data data;
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return receive(unit_type, data, _tag);
}

}

#endif

