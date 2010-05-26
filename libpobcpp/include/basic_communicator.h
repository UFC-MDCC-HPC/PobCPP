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

// Point-to-Point
public:
	//FIXME implement array send and receive
	template<typename Type, typename Data>
	void send(const Data& data, const int tag, unsigned int _enumi = 0);

	template<typename Type, typename Data>
	Data receive(const int _tag, unsigned int _enumi = 0);

// Collective
	template<typename Type, typename Data>
	void broadcast(Data& value, unsigned int _enumi = 0);
	template<typename Type, typename Data>
	void broadcast(Data* values, int n, unsigned int _enumi = 0);

	template<typename Type, typename Data>
	void gather(const Data& in_value, Data* out_values, unsigned int _enumi = 0);
	template<typename Type, typename Data>
	void gather(const Data* in_values, int n, Data* out_values, unsigned int _enumi = 0);

private:
	// Implementations
	void send(const Unit_Type& _unit_type, const int& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const unsigned int& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const float& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const double& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const char& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const std::string& _data, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<int, int> & _data, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<float, int> & _data, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<double, int> & _data, const int _tag);

	int receive(const Unit_Type& _unit_type, const int& _data_type, const int _tag);
	unsigned int receive(const Unit_Type& _unit_type, const unsigned int& _data_type, const int _tag);
	float receive(const Unit_Type& _unit_type, const float& _data_type, const int _tag);
	double receive(const Unit_Type& _unit_type, const double& _data_type, const int _tag);
	char receive(const Unit_Type& _unit_type, const char& _data_type, const int _tag);
	std::string receive(const Unit_Type& _unit_type, const std::string& _data_type, const int _tag);
	std::pair<int, int> receive(const Unit_Type& _unit_type, const std::pair<int, int>& _data_type, const int _tag);
	std::pair<float, int> receive(const Unit_Type& _unit_type, const std::pair<float, int>& _data_type, const int _tag);
	std::pair<double, int> receive(const Unit_Type& _unit_type, const std::pair<double, int>& _data_type, const int _tag);

	void broadcast(const Unit_Type& _unit_type, int& value);
	void broadcast(const Unit_Type& _unit_type, unsigned int& value);
	void broadcast(const Unit_Type& _unit_type, float& value);
	void broadcast(const Unit_Type& _unit_type, double& value);
	void broadcast(const Unit_Type& _unit_type, char& value);
	void broadcast(const Unit_Type& _unit_type, std::string& value);
	void broadcast(const Unit_Type& _unit_type, std::pair<int, int>& value);
	void broadcast(const Unit_Type& _unit_type, std::pair<float, int>& value);
	void broadcast(const Unit_Type& _unit_type, std::pair<double, int>& value);

	void broadcast(const Unit_Type& _unit_type, int* values, int n);
	void broadcast(const Unit_Type& _unit_type, unsigned int* values, int n);
	void broadcast(const Unit_Type& _unit_type, float* values, int n);
	void broadcast(const Unit_Type& _unit_type, double* values, int n);
	void broadcast(const Unit_Type& _unit_type, char* values, int n);
	void broadcast(const Unit_Type& _unit_type, std::string* value, int n);
	void broadcast(const Unit_Type& _unit_type, std::pair<int, int>* values, int n);
	void broadcast(const Unit_Type& _unit_type, std::pair<float, int>* values, int n);
	void broadcast(const Unit_Type& _unit_type, std::pair<double, int>* values, int n);

	void gather(const Unit_Type& _unit_type, const int& in_value, int* out_values);
	void gather(const Unit_Type& _unit_type, const unsigned int& in_value, unsigned int* out_values);
	void gather(const Unit_Type& _unit_type, const float& in_value, float* out_values);
	void gather(const Unit_Type& _unit_type, const double& in_value, double* out_values);
	void gather(const Unit_Type& _unit_type, const char& in_value, char* out_values);
	void gather(const Unit_Type& _unit_type, const std::string& in_value, std::string* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<int, int>& in_value, std::pair<int, int>* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<float, int>& in_value, std::pair<float, int>* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<double, int>& in_value, std::pair<double, int>* out_values);
	
	void gather(const Unit_Type& _unit_type, const int* in_values, int n, int* out_values);
	void gather(const Unit_Type& _unit_type, const unsigned int* in_values, int n, unsigned int* out_values);
	void gather(const Unit_Type& _unit_type, const float* in_values, int n, float* out_values);
	void gather(const Unit_Type& _unit_type, const double* in_values, int n, double* out_values);
	void gather(const Unit_Type& _unit_type, const char* in_values, int n, char* out_values);
	void gather(const Unit_Type& _unit_type, const std::string* in_values, int n, std::string* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<int, int>* in_values, int n, std::pair<int, int>* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<float, int>* in_values, int n, std::pair<float, int>* out_values);
	void gather(const Unit_Type& _unit_type, const std::pair<double, int>* in_values, int n, std::pair<double, int>* out_values);
private:

	Environment* env;
	MPI_Comm comm;
};

template<typename Type, typename Data>
void Basic_Communicator::send(const Data& _data, const int _tag, unsigned int _enumi) {
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

template<typename Type, typename Data>
void Basic_Communicator::broadcast(Data& value, unsigned int _enumi) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return broadcast(unit_type, value);
}

template<typename Type, typename Data>
void Basic_Communicator::broadcast(Data* value, int n, unsigned int _enumi) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return broadcast(unit_type, value, n);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const Data& in_value, Data* out_values, unsigned int _enumi) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return gather(unit_type, in_value, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const Data* in_values, int n, Data* out_values, unsigned int _enumi) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return gather(unit_type, in_values, n, out_values);
}
}

#endif

