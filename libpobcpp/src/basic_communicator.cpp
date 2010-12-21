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
		} \
	} \
} 

#define Basic_Communicator_send_array_impl(datatype) \
void Basic_Communicator::send(const Unit_Type& _unit_type, const datatype* _data, int n, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.send(unit_rank, _tag, _data, n);	\
		} \
	} \
} 

#define Basic_Communicator_isend_impl(datatype) \
void Basic_Communicator::isend(const Unit_Type& _unit_type, const datatype& _data, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.isend(unit_rank, _tag, _data);	\
		} \
	} \
} 

#define Basic_Communicator_isend_array_impl(datatype) \
void Basic_Communicator::isend(const Unit_Type& _unit_type, const datatype* _data, int n, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.isend(unit_rank, _tag, _data, n);	\
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
		} \
	} \
	return data; \
} 

#define Basic_Communicator_receive_array_impl(datatype) \
void Basic_Communicator::receive(const Unit_Type& _unit_type, datatype* data, int n, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.recv(unit_rank , _tag, data, n); \
		} \
	} \
} 

#define Basic_Communicator_ireceive_impl(datatype) \
datatype Basic_Communicator::ireceive(const Unit_Type& _unit_type, const datatype& _data_type, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	datatype data; \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.irecv(unit_rank , _tag, data); \
		} \
	} \
	return data; \
} 

#define Basic_Communicator_ireceive_array_impl(datatype) \
datatype Basic_Communicator::ireceive(const Unit_Type& _unit_type, const datatype* _data_type, int n, const int _tag) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	datatype data; \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			world.irecv(unit_rank , _tag, data, n); \
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
		} \
	} \
}

#define Basic_Communicator_gather_array_impl(datatype) \
void Basic_Communicator::gather(const Unit_Type& _unit_type, const datatype* in_values, int n, datatype* out_values) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			boost::mpi::gather(world, in_values, n, out_values, unit_rank); \
		} \
	} \
}

#define Basic_Communicator_scatter_impl(datatype) \
void Basic_Communicator::scatter(const Unit_Type& _unit_type, const datatype* in_values, datatype& out_value) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
  if(env && world) { \
    if(env->isComplete()) { \
      unsigned int unit_rank = env->get_rank(_unit_type); \
      boost::mpi::scatter(world, in_values, out_value, unit_rank); \
    } \
  } \
}

#define Basic_Communicator_scatter_array_impl(datatype) \
void Basic_Communicator::scatter(const Unit_Type& _unit_type, const datatype* in_values, datatype* out_values, int n) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
  if(env && world) { \
    if(env->isComplete()) { \
      unsigned int unit_rank = env->get_rank(_unit_type); \
      boost::mpi::scatter(world, in_values, out_values, n, unit_rank); \
    } \
  } \
}

#define Basic_Communicator_send_and_isend_impl(datatype) \
	Basic_Communicator_send_impl(datatype) \
	Basic_Communicator_send_array_impl(datatype) \
	Basic_Communicator_isend_impl(datatype) \
	Basic_Communicator_isend_array_impl(datatype) \

namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : env(0)  { }

Basic_Communicator::~Basic_Communicator() { }

void Basic_Communicator::set_environment(Environment* _env) { 
		env = _env;
}

void Basic_Communicator::set_intracomm(MPI_Comm _comm) {
	comm = _comm;
}

MPI_Comm Basic_Communicator::getMPIComm() {
	return comm;
}

typedef std::pair<int, int> pair_int_int;
typedef std::pair<float, int> pair_float_int;
typedef std::pair<double, int> pair_double_int;

Basic_Communicator_send_and_isend_impl(int);
Basic_Communicator_send_and_isend_impl(unsigned int);
Basic_Communicator_send_and_isend_impl(float);
Basic_Communicator_send_and_isend_impl(double);
Basic_Communicator_send_and_isend_impl(char);
Basic_Communicator_send_and_isend_impl(std::string);
Basic_Communicator_send_and_isend_impl(pair_int_int);
Basic_Communicator_send_and_isend_impl(pair_float_int);
Basic_Communicator_send_and_isend_impl(pair_double_int);

Basic_Communicator_receive_impl(int);
Basic_Communicator_receive_impl(unsigned int);
Basic_Communicator_receive_impl(float);
Basic_Communicator_receive_impl(double);
Basic_Communicator_receive_impl(char);
Basic_Communicator_receive_impl(std::string);
Basic_Communicator_receive_impl(pair_int_int);
Basic_Communicator_receive_impl(pair_float_int);
Basic_Communicator_receive_impl(pair_double_int);

Basic_Communicator_receive_array_impl(int);
Basic_Communicator_receive_array_impl(unsigned int);
Basic_Communicator_receive_array_impl(float);
Basic_Communicator_receive_array_impl(double);
Basic_Communicator_receive_array_impl(char);
Basic_Communicator_receive_array_impl(std::string);
Basic_Communicator_receive_array_impl(pair_int_int);
Basic_Communicator_receive_array_impl(pair_float_int);
Basic_Communicator_receive_array_impl(pair_double_int);

Basic_Communicator_broadcast_impl(int);
Basic_Communicator_broadcast_impl(unsigned int);
Basic_Communicator_broadcast_impl(float);
Basic_Communicator_broadcast_impl(double);
Basic_Communicator_broadcast_impl(char);
Basic_Communicator_broadcast_impl(std::string);
Basic_Communicator_broadcast_impl(pair_int_int);
Basic_Communicator_broadcast_impl(pair_float_int);
Basic_Communicator_broadcast_impl(pair_double_int);

Basic_Communicator_broadcast_array_impl(int);
Basic_Communicator_broadcast_array_impl(unsigned int);
Basic_Communicator_broadcast_array_impl(float);
Basic_Communicator_broadcast_array_impl(double);
Basic_Communicator_broadcast_array_impl(char);
Basic_Communicator_broadcast_array_impl(std::string);
Basic_Communicator_broadcast_array_impl(pair_int_int);
Basic_Communicator_broadcast_array_impl(pair_float_int);
Basic_Communicator_broadcast_array_impl(pair_double_int);

Basic_Communicator_gather_impl(int);
Basic_Communicator_gather_impl(unsigned int);
Basic_Communicator_gather_impl(float);
Basic_Communicator_gather_impl(double);
Basic_Communicator_gather_impl(char);
Basic_Communicator_gather_impl(std::string);
Basic_Communicator_gather_impl(pair_int_int);
Basic_Communicator_gather_impl(pair_float_int);
Basic_Communicator_gather_impl(pair_double_int);

Basic_Communicator_gather_array_impl(int);
Basic_Communicator_gather_array_impl(unsigned int);
Basic_Communicator_gather_array_impl(float);
Basic_Communicator_gather_array_impl(double);
Basic_Communicator_gather_array_impl(char);
Basic_Communicator_gather_array_impl(std::string);
Basic_Communicator_gather_array_impl(pair_int_int);
Basic_Communicator_gather_array_impl(pair_float_int);
Basic_Communicator_gather_array_impl(pair_double_int);

//Basic_Communicator_scatter_impl(int); // FIXME
Basic_Communicator_scatter_impl(unsigned int);
Basic_Communicator_scatter_impl(float);
Basic_Communicator_scatter_impl(double);
Basic_Communicator_scatter_impl(char);
Basic_Communicator_scatter_impl(std::string);
Basic_Communicator_scatter_impl(pair_int_int);
Basic_Communicator_scatter_impl(pair_float_int);
Basic_Communicator_scatter_impl(pair_double_int);

Basic_Communicator_scatter_array_impl(int);
Basic_Communicator_scatter_array_impl(unsigned int);
Basic_Communicator_scatter_array_impl(float);
Basic_Communicator_scatter_array_impl(double);
Basic_Communicator_scatter_array_impl(char);
Basic_Communicator_scatter_array_impl(std::string);
Basic_Communicator_scatter_array_impl(pair_int_int);
Basic_Communicator_scatter_array_impl(pair_float_int);
Basic_Communicator_scatter_array_impl(pair_double_int);

void Basic_Communicator::reduce(const Unit_Type& _unit_type, const double* in_values, int n, double* out_values) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	if(env && world) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			boost::mpi::reduce(world, in_values, n, out_values, std::plus<double>(), unit_rank);
		}
	}
}
void Basic_Communicator::reduce(const Unit_Type& _unit_type, const double* in_values, int n) {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	if(env && world) {
		if(env->isComplete()) {
			unsigned int unit_rank = env->get_rank(_unit_type);
			boost::mpi::reduce(world, in_values, n, std::plus<double>(), unit_rank);
		}
	}
}
}


