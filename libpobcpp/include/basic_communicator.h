#ifndef __BASIC_COMMUNICATOR_H__
#define __BASIC_COMMUNICATOR_H__

#include "unit_type.h"
#include "communicator.h"
#include "environment.h"
#include <mpi.h>
#include <map> // std::pair

#include <string>

namespace Pobcpp {
//Move to a new file

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
	void send(const Data& data, const int tag);
	template<typename Type, typename Data>
	void send(const unsigned int _enumi, const Data& data, const int tag);

	template<typename Type, typename Data>
	void send(const Data* data, int n, const int tag);
	template<typename Type, typename Data>
	void send(const unsigned int _enumi, const Data* data, int n, const int tag);

	template<typename Type, typename Data>
	void isend(const Data& data, const int tag);
	template<typename Type, typename Data>
	void isend(const unsigned int _enumi, const Data& data, const int tag);

	template<typename Type, typename Data>
	void isend(const Data* data, int n, const int tag);
	template<typename Type, typename Data>
	void isend(const unsigned int _enumi, const Data* data, int n, const int tag);

	template<typename Type, typename Data>
	Data receive(const unsigned int _enumi, const int _tag);
	template<typename Type, typename Data>
	Data receive(const int _tag);
	template<typename Type, typename Data>
	void receive(const unsigned int _enumi, Data* data, int n, const int _tag);
	template<typename Type, typename Data>
	void receive(Data* data, int n, const int _tag);

// Collective
	template<typename Type, typename Data>
	void broadcast(Data& value);
	template<typename Type, typename Data>
	void broadcast(const unsigned int _enumi, Data& value);
	template<typename Type, typename Data>
	void broadcast(Data* values, int n);
	template<typename Type, typename Data>
	void broadcast(const unsigned int _enumi, Data* values, int n);

	template<typename Type, typename Data>
	void gather(const Data& in_value, Data* out_values);
	template<typename Type, typename Data>
	void gather(const unsigned int _enumi, const Data& in_value, Data* out_values);
	template<typename Type, typename Data>
	void gather(const Data* in_values, int n, Data* out_values);
	template<typename Type, typename Data>
	void gather(const unsigned int _enumi, const Data* in_values, int n, Data* out_values);

  template<typename Type, typename Data>
  void scatter(const Data* in_value, Data& out_values);
  template<typename Type, typename Data>
  void scatter(const unsigned int _enumi, const Data* in_value, Data& out_values);
  template<typename Type, typename Data>
  void scatter(const Data* in_values, Data* out_values, int n);
  template<typename Type, typename Data>
  void scatter(const unsigned int _enumi, const Data* in_values, Data* out_values, int n);

	template<typename Type, typename Data>
	void reduce(const Data* in_values, int n);	
	template<typename Type, typename Data>
	void reduce(const unsigned int _enumi, const Data* in_values, int n);	
	template<typename Type, typename Data>
	void reduce(const Data* in_values, int n, Data* out_values);	
	template<typename Type, typename Data>
	void reduce(const unsigned int _enumi, const Data* in_values, int n, Data* out_values);	

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

	void send(const Unit_Type& _unit_type, const int* _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const unsigned int* _data, int n ,const int _tag);
	void send(const Unit_Type& _unit_type, const float* _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const double* _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const char* _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const std::string* _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<int, int> * _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<float, int> * _data, int n, const int _tag);
	void send(const Unit_Type& _unit_type, const std::pair<double, int> * _data, int n, const int _tag);

	void isend(const Unit_Type& _unit_type, const int& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const unsigned int& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const float& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const double& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const char& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::string& _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<int, int> & _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<float, int> & _data, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<double, int> & _data, const int _tag);

	void isend(const Unit_Type& _unit_type, const int* _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const unsigned int* _data, int n ,const int _tag);
	void isend(const Unit_Type& _unit_type, const float* _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const double* _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const char* _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::string* _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<int, int> * _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<float, int> * _data, int n, const int _tag);
	void isend(const Unit_Type& _unit_type, const std::pair<double, int> * _data, int n, const int _tag);
	
	int receive(const Unit_Type& _unit_type, const int& _data_type, const int _tag);
	unsigned int receive(const Unit_Type& _unit_type, const unsigned int& _data_type, const int _tag);
	float receive(const Unit_Type& _unit_type, const float& _data_type, const int _tag);
	double receive(const Unit_Type& _unit_type, const double& _data_type, const int _tag);
	char receive(const Unit_Type& _unit_type, const char& _data_type, const int _tag);
	std::string receive(const Unit_Type& _unit_type, const std::string& _data_type, const int _tag);
	std::pair<int, int> receive(const Unit_Type& _unit_type, const std::pair<int, int>& _data_type, const int _tag);
	std::pair<float, int> receive(const Unit_Type& _unit_type, const std::pair<float, int>& _data_type, const int _tag);
	std::pair<double, int> receive(const Unit_Type& _unit_type, const std::pair<double, int>& _data_type, const int _tag);

	void receive(const Unit_Type& _unit_type, int* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, unsigned int* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, float* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, double* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, char* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, std::string* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, std::pair<int, int>* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, std::pair<float, int>* _data_type, int n, const int _tag);
	void receive(const Unit_Type& _unit_type, std::pair<double, int>* _data_type, int n, const int _tag);

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

  void scatter(const Unit_Type& _unit_type, const int* in_value, int& out_values);
  void scatter(const Unit_Type& _unit_type, const unsigned int* in_value, unsigned int& out_values);
  void scatter(const Unit_Type& _unit_type, const float* in_value, float& out_values);
  void scatter(const Unit_Type& _unit_type, const double* in_value, double& out_values);
  void scatter(const Unit_Type& _unit_type, const char* in_value, char& out_values);
  void scatter(const Unit_Type& _unit_type, const std::string* in_value, std::string& out_values);
  void scatter(const Unit_Type& _unit_type, const std::pair<int, int>* in_value, std::pair<int, int>& out_values);
  void scatter(const Unit_Type& _unit_type, const std::pair<float, int>* in_value, std::pair<float, int>& out_values);
  void scatter(const Unit_Type& _unit_type, const std::pair<double, int>* in_value, std::pair<double, int>& out_values);

  void scatter(const Unit_Type& _unit_type, const int* in_values, int* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const unsigned int* in_values, unsigned int* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const float* in_values, float* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const double* in_values, double* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const char* in_values, char* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const std::string* in_values, std::string* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const std::pair<int, int>* in_values, std::pair<int, int>* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const std::pair<float, int>* in_values, std::pair<float, int>* out_values, int n);
  void scatter(const Unit_Type& _unit_type, const std::pair<double, int>* in_values, std::pair<double, int>* out_values, int n);

	void reduce(const Unit_Type& _unit_type, const double* in_values, int n, double* out_values);
	void reduce(const Unit_Type& _unit_type, const double* in_values, int n);
private:

	Environment* env;
	MPI_Comm comm;
};

template<typename Type, typename Data>
void Basic_Communicator::send(const Data& _data, const int _tag) {
	send<Type>(0, _data, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::send(const unsigned int _enumi, const Data& _data, const int _tag) {
	Type* un;
	Unit_Type unit_type(un);
	unit_type.set_enums(std::make_pair(_enumi,0));
	send(unit_type, _data, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::send(const Data* _data, int n, const int _tag) {
	send<Type>(0, _data, n, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::send(const unsigned int _enumi, const Data* _data, int n, const int _tag) {
	Type* un;
	Unit_Type unit_type(un);
	unit_type.set_enums(std::make_pair(_enumi,0));
	send(unit_type, _data, n, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::isend(const Data& _data, const int _tag) {
	isend<Type>(0, _data, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::isend(const unsigned int _enumi, const Data& _data, const int _tag) {
	Type* un;
	Unit_Type unit_type(un);
	unit_type.set_enums(std::make_pair(_enumi,0));
	isend(unit_type, _data, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::isend(const Data* _data, int n, const int _tag) {
	isend<Type>(0, _data, n, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::isend(const unsigned int _enumi, const Data* _data, int n, const int _tag) {
	Type* un;
	Unit_Type unit_type(un);
	unit_type.set_enums(std::make_pair(_enumi,0));
	isend(unit_type, _data, n, _tag);
}


template<typename Type, typename Data>
Data Basic_Communicator::receive(const int _tag) {
	return receive<Type, Data>(0, _tag);
}

template<typename Type, typename Data>
Data Basic_Communicator::receive(const unsigned int _enumi, const int _tag) {
	Data data;
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return receive(unit_type, data, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::receive(Data* data, int n, const int _tag) {
	receive<Type, Data>(0, data, n, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::receive(const unsigned int _enumi, Data* data, int n, const int _tag) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	receive(unit_type, data, n, _tag);
}

template<typename Type, typename Data>
void Basic_Communicator::broadcast(Data& value) {
	return broadcast<Type>(0, value);
}

template<typename Type, typename Data>
void Basic_Communicator::broadcast(const unsigned int _enumi, Data& value) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return broadcast(unit_type, value);
}

template<typename Type, typename Data>
void Basic_Communicator::broadcast(Data* value, int n) {
	return broadcast<Type>(0, value, n);
}

template<typename Type, typename Data>
void Basic_Communicator::broadcast(const unsigned int _enumi, Data* value, int n) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return broadcast(unit_type, value, n);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const Data& in_value, Data* out_values) {
	return gather<Type>(0, in_value, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const unsigned int _enumi, const Data& in_value, Data* out_values) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return gather(unit_type, in_value, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const Data* in_values, int n, Data* out_values) {
	return gather<Type>(0, in_values, n, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::gather(const unsigned int _enumi, const Data* in_values, int n, Data* out_values) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return gather(unit_type, in_values, n, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::scatter(const Data* in_values, Data& out_value) {
  return scatter<Type>(0, in_values, out_value);
}

template<typename Type, typename Data>
void Basic_Communicator::scatter(const unsigned int _enumi, const Data* in_values, Data& out_value) {
  Type* un;
  Unit_Type unit_type(un);
  unit_type.set_enums(std::make_pair(_enumi,0));
  return scatter(unit_type, in_values, out_value);
}

template<typename Type, typename Data>
void Basic_Communicator::scatter(const Data* in_values, Data* out_values, int n) {
  return scatter<Type>(0, in_values, out_values, n);
}

template<typename Type, typename Data>
void Basic_Communicator::scatter(const unsigned int _enumi, const Data* in_values, Data* out_values, int n) {
  Type* un;
  Unit_Type unit_type(un);
  unit_type.set_enums(std::make_pair(_enumi,0));
  return scatter(unit_type, in_values,out_values, n);
}

template<typename Type, typename Data>
void Basic_Communicator::reduce(const Data* in_values, int n) {
	return reduce<Type>(0, in_values, n);
}

template<typename Type, typename Data>
void Basic_Communicator::reduce(const unsigned int _enumi, const Data* in_values, int n) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return reduce(unit_type, in_values, n);
}

template<typename Type, typename Data>
void Basic_Communicator::reduce(const Data* in_values, int n, Data* out_values) {
	return reduce<Type>(0, in_values, n, out_values);
}

template<typename Type, typename Data>
void Basic_Communicator::reduce(const unsigned int _enumi, const Data* in_values, int n, Data* out_values) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return reduce(unit_type, in_values, n, out_values);
}

}

#endif

