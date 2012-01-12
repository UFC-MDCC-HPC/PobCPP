#ifndef __BASIC_COMMUNICATOR_H__
#define __BASIC_COMMUNICATOR_H__

#include "unit_type.h"
#include "environment.h"
#include "group.h"
#include <mpi.h>
#include <map> // std::pair

#include <string>

typedef std::pair<int, int> pair_int_int;
typedef std::pair<float, int> pair_float_int;
typedef std::pair<double, int> pair_double_int;

#define send_decl(datatype) \
void send(int dest, int tag, const datatype& value) const;
#define send_array_decl(datatype) \
void send(int dest, int tag, const datatype* values, int n) const;

#define isend_decl(datatype) \
MPI_Request isend(int dest, int tag, const datatype& value) const;
#define isend_array_decl(datatype) \
MPI_Request isend(int dest, int tag, const datatype* values, int n) const;

#define recv_decl(datatype) \
MPI_Status recv(int source, int tag, datatype& value) const;
#define recv_array_decl(datatype) \
MPI_Status recv(int source, int tag, datatype* values, int n) const;

#define irecv_decl(datatype) \
MPI_Request irecv(int source, int tag, datatype& value) const;
#define irecv_array_decl(datatype) \
MPI_Request irecv(int source, int tag, datatype* values, int n) const;

#define bcast_decl(datatype) \
	void broadcast(datatype& value, int root);
#define bcast_array_decl(datatype) \
	void broadcast(datatype* value, int n, int root);

#define reduce_decl(datatype) \
void reduce(const datatype* in_values, int n, int root);
#define reduce_decl2(datatype) \
void reduce(const datatype* in_values, int n, datatype* out_values, int root);

namespace Pobcpp {
//Move to a new file


class Basic_Communicator {
public:
	Basic_Communicator(); 
	~Basic_Communicator();
	MPI_Comm get_mpi_comm(); // Internal data
	void set_environment(Environment* _env); // FIXME
	void set_intracomm(MPI_Comm _comm); // FIXME
private:
	friend class Unit;
	Basic_Communicator(MPI_Comm comm);
public:
// Communicator handling	
//Split
//Create
//etc
	int rank() const;
	int size() const;
	void barrier() const;
	Group group() const;
	Basic_Communicator create(Group group);

// Send
	send_decl(int)
	send_decl(unsigned int);
	send_decl(float);
	send_decl(double);
	send_decl(char);
	send_decl(std::string);
	send_decl(pair_int_int);
	send_decl(pair_float_int);
	send_decl(pair_double_int);

	send_array_decl(int)
	send_array_decl(unsigned int);
	send_array_decl(float);
	send_array_decl(double);
	send_array_decl(char);
	send_array_decl(std::string);
	send_array_decl(pair_int_int);
	send_array_decl(pair_float_int);
	send_array_decl(pair_double_int);

	isend_decl(int)
	isend_decl(unsigned int);
	isend_decl(float);
	isend_decl(double);
	isend_decl(char);
	isend_decl(std::string);
	isend_decl(pair_int_int);
	isend_decl(pair_float_int);
	isend_decl(pair_double_int);

	isend_array_decl(int)
	isend_array_decl(unsigned int);
	isend_array_decl(float);
	isend_array_decl(double);
	isend_array_decl(char);
	isend_array_decl(std::string);
	isend_array_decl(pair_int_int);
	isend_array_decl(pair_float_int);
	isend_array_decl(pair_double_int);

// Receive
	recv_decl(int)
	recv_decl(unsigned int);
	recv_decl(float);
	recv_decl(double);
	recv_decl(char);
	recv_decl(std::string);
	recv_decl(pair_int_int);
	recv_decl(pair_float_int);
	recv_decl(pair_double_int);

	recv_array_decl(int)
	recv_array_decl(unsigned int);
	recv_array_decl(float);
	recv_array_decl(double);
	recv_array_decl(char);
	recv_array_decl(std::string);
	recv_array_decl(pair_int_int);
	recv_array_decl(pair_float_int);
	recv_array_decl(pair_double_int);

	irecv_decl(int)
	irecv_decl(unsigned int);
	irecv_decl(float);
	irecv_decl(double);
	irecv_decl(char);
	irecv_decl(std::string);
	irecv_decl(pair_int_int);
	irecv_decl(pair_float_int);
	irecv_decl(pair_double_int);

	irecv_array_decl(int)
	irecv_array_decl(unsigned int);
	irecv_array_decl(float);
	irecv_array_decl(double);
	irecv_array_decl(char);
	irecv_array_decl(std::string);
	irecv_array_decl(pair_int_int);
	irecv_array_decl(pair_float_int);
	irecv_array_decl(pair_double_int);

	// Collective

	bcast_decl(int)
	bcast_decl(unsigned int);
	bcast_decl(float);
	bcast_decl(double);
	bcast_decl(char);
	bcast_decl(std::string);
	bcast_decl(pair_int_int);
	bcast_decl(pair_float_int);
	bcast_decl(pair_double_int);

	bcast_array_decl(int)
	bcast_array_decl(unsigned int);
	bcast_array_decl(float);
	bcast_array_decl(double);
	bcast_array_decl(char);
	bcast_array_decl(std::string);
	bcast_array_decl(pair_int_int);
	bcast_array_decl(pair_float_int);
	bcast_array_decl(pair_double_int);

  reduce_decl(int)
  reduce_decl(unsigned int);
  reduce_decl(float);
  reduce_decl(double);
  reduce_decl(char);
  reduce_decl(std::string);
  reduce_decl(pair_int_int);
  reduce_decl(pair_float_int);
  reduce_decl(pair_double_int);

  reduce_decl2(int)
  reduce_decl2(unsigned int);
  reduce_decl2(float);
  reduce_decl2(double);
  reduce_decl2(char);
  reduce_decl2(std::string);
  reduce_decl2(pair_int_int);
  reduce_decl2(pair_float_int);
  reduce_decl2(pair_double_int);


// Collective
/*
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
*/

private:

	Environment* env;
	MPI_Comm comm;
};
/*
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
Data Basic_Communicator::receive(const int _tag, MPI_Status* status) {
	return receive<Type, Data>(0, _tag, status);
}

template<typename Type, typename Data>
Data Basic_Communicator::receive(const unsigned int _enumi, const int _tag, MPI_Status* status) {
	Data data;
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	return receive(unit_type, data, _tag, status);
}

template<typename Type, typename Data>
void Basic_Communicator::receive(Data* data, int n, const int _tag, MPI_Status* status) {
	receive<Type, Data>(0, data, n, _tag, status);
}

template<typename Type, typename Data>
void Basic_Communicator::receive(const unsigned int _enumi, Data* data, int n, const int _tag, MPI_Status* status) {
	Type* un;
	Unit_Type unit_type(un);	
	unit_type.set_enums(std::make_pair(_enumi,0));
	receive(unit_type, data, n, _tag, status);
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
*/
typedef Basic_Communicator Communicator;

}

#endif

