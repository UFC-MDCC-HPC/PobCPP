#ifndef __BASIC_COMMUNICATOR_H__
#define __BASIC_COMMUNICATOR_H__

#include "unit_type.h"
#include "communicator.h"
#include "environment.h"

namespace Pobcpp {

class Basic_Communicator {
public:
	Basic_Communicator(); 
	~Basic_Communicator();

	void set_environment(Environment* _env);
	
	template<typename Type, typename Data>
	void send(Data data, const int tag);

	void send(const Unit_Type& _unit_type, int _data, const int _tag);

	template<typename Type, typename Data>
	Data receive(const int _tag);

	int receive(const Unit_Type& _unit_type, int _data_type, const int _tag);

private:

	Environment* env;
};

template<typename Type, typename Data>
void Basic_Communicator::send(Data _data, const int _tag) {
		Type* un;
		Unit_Type unit_type(un);	
		send(unit_type, _data, _tag);
}

template<typename Type, typename Data>
Data Basic_Communicator::receive(const int _tag) {
	Data data;
	Type* un;
	Unit_Type unit_type(un);	
	return receive(unit_type, data, _tag);
}

}

#endif

