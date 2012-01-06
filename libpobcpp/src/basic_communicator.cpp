#include "basic_communicator.h"
#include "communication.h"
#include <boost/mpi/collectives.hpp>
#include <iostream>
#include <mpi.h>

#define Basic_Communicator_send_impl(datatype) \
void Basic_Communicator::send(int dest, int tag, const datatype& value) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	world.send(dest, tag , value);\
}
#define Basic_Communicator_send_array_impl(datatype) \
void Basic_Communicator::send(int dest, int tag, const datatype* values, int n) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	world.send(dest, tag , values, n);\
}
#define Basic_Communicator_isend_impl(datatype) \
MPI_Request Basic_Communicator::isend(int dest, int tag, const datatype& value) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.isend(dest, tag , value).m_requests[0];\
}

#define Basic_Communicator_isend_array_impl(datatype) \
MPI_Request Basic_Communicator::isend(int dest, int tag, const datatype* values, int n) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.isend(dest, tag , values, n).m_requests[0];\
}

#define Basic_Communicator_recv_impl(datatype) \
MPI_Status Basic_Communicator::recv(int source, int tag, datatype& value) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.recv(source, tag, value); \
}

#define Basic_Communicator_recv_array_impl(datatype) \
MPI_Status Basic_Communicator::recv(int source, int tag, datatype* values, int n) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.recv(source, tag, values, n); \
}

#define Basic_Communicator_irecv_impl(datatype) \
MPI_Request Basic_Communicator::irecv(int source, int tag, datatype& value) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.irecv(source, tag, value).m_requests[0]; \
}

#define Basic_Communicator_irecv_array_impl(datatype) \
MPI_Request Basic_Communicator::irecv(int source, int tag, datatype* values, int n) const { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return world.irecv(source, tag, values, n).m_requests[0];\
}

#define Basic_Communicator_bcast_impl(datatype) \
	void Basic_Communicator::broadcast(datatype& value, int root) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return boost::mpi::broadcast(world, value, root);	\
}

#define Basic_Communicator_bcast_array_impl(datatype) \
	void Basic_Communicator::broadcast(datatype* value, int n, int root) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	return boost::mpi::broadcast(world, value, n, root);	\
}


#define Basic_Communicator_reduce_impl(datatype) \
void Basic_Communicator::reduce(const datatype* in_values, int n, datatype* out_values, int root) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
  if(env && world) { \
    if(env->isComplete()) { \
      boost::mpi::reduce(world, in_values, n, out_values, std::plus<datatype>(), root); \
    } \
  } \
}

#define Basic_Communicator_reduce_impl2(datatype) \
void Basic_Communicator::reduce(const datatype* in_values, int n, int root) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
  if(env && world) { \
    if(env->isComplete()) { \
      boost::mpi::reduce(world, in_values, n, std::plus<datatype>(), root); \
    } \
  } \
}

/*
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
datatype Basic_Communicator::receive(const Unit_Type& _unit_type, const datatype& _data_type, const int _tag, MPI_Status* status) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	datatype data; \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			*status = (world.recv(unit_rank , _tag, data)); \
		} \
	} \
	return data; \
} 

#define Basic_Communicator_receive_array_impl(datatype) \
void Basic_Communicator::receive(const Unit_Type& _unit_type, datatype* data, int n, const int _tag, MPI_Status* status) { \
	boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(env && world) { \
		if(env->isComplete()) { \
			unsigned int unit_rank = env->get_rank(_unit_type); \
			*status = world.recv(unit_rank , _tag, data, n); \
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
*/
#define Basic_Communicator_send_and_isend_impl(datatype) \
	Basic_Communicator_send_impl(datatype) \
	Basic_Communicator_send_array_impl(datatype) \
	Basic_Communicator_isend_impl(datatype) \
	Basic_Communicator_isend_array_impl(datatype)
#define Basic_Communicator_recv_and_irecv_impl(datatype) \
	Basic_Communicator_recv_impl(datatype) \
	Basic_Communicator_recv_array_impl(datatype) \
	Basic_Communicator_irecv_impl(datatype) \
	Basic_Communicator_irecv_array_impl(datatype)
#define Basic_Communicator_bcast(datatype) \
	Basic_Communicator_bcast_impl(datatype) \
	Basic_Communicator_bcast_array_impl(datatype) 
namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : env(0), comm(MPI_COMM_WORLD)  { }

Basic_Communicator::Basic_Communicator(MPI_Comm comm) : comm(comm) {

}

Basic_Communicator::~Basic_Communicator() { }

MPI_Comm Basic_Communicator::get_mpi_comm() {
	return comm;
}

void Basic_Communicator::set_environment(Environment* _env) { 
		env = _env;
}

void Basic_Communicator::set_intracomm(MPI_Comm _comm) {
	comm = _comm;
}

int Basic_Communicator::rank() const {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	return world.rank();
}

int Basic_Communicator::size() const {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	return world.size();
}

Group Basic_Communicator::group() const {
	MPI_Group grp;
	MPI_Comm_group(comm, &grp);
	return Group(grp);
}

Basic_Communicator Basic_Communicator::create(Group group) {
	MPI_Comm newcomm;
	MPI_Comm_create(comm, group.get_mpi_group(), &newcomm);
	return Basic_Communicator(newcomm);
}


Basic_Communicator_send_and_isend_impl(int);
Basic_Communicator_send_and_isend_impl(unsigned int);
Basic_Communicator_send_and_isend_impl(float);
Basic_Communicator_send_and_isend_impl(double);
Basic_Communicator_send_and_isend_impl(char);
Basic_Communicator_send_and_isend_impl(std::string);
Basic_Communicator_send_and_isend_impl(pair_int_int);
Basic_Communicator_send_and_isend_impl(pair_float_int);
Basic_Communicator_send_and_isend_impl(pair_double_int);

Basic_Communicator_recv_and_irecv_impl(int);
Basic_Communicator_recv_and_irecv_impl(unsigned int);
Basic_Communicator_recv_and_irecv_impl(float);
Basic_Communicator_recv_and_irecv_impl(double);
Basic_Communicator_recv_and_irecv_impl(char);
Basic_Communicator_recv_and_irecv_impl(std::string);
Basic_Communicator_recv_and_irecv_impl(pair_int_int);
Basic_Communicator_recv_and_irecv_impl(pair_float_int);
Basic_Communicator_recv_and_irecv_impl(pair_double_int);

Basic_Communicator_bcast_impl(int);
Basic_Communicator_bcast_impl(unsigned int);
Basic_Communicator_bcast_impl(float);
Basic_Communicator_bcast_impl(double);
Basic_Communicator_bcast_impl(char);
Basic_Communicator_bcast_impl(std::string);

Basic_Communicator_reduce_impl(int);
Basic_Communicator_reduce_impl(unsigned int);
Basic_Communicator_reduce_impl(float);
Basic_Communicator_reduce_impl(double);
Basic_Communicator_reduce_impl(char);
Basic_Communicator_reduce_impl(std::string);

Basic_Communicator_reduce_impl2(int);
Basic_Communicator_reduce_impl2(unsigned int);
Basic_Communicator_reduce_impl2(float);
Basic_Communicator_reduce_impl2(double);
Basic_Communicator_reduce_impl2(char);
Basic_Communicator_reduce_impl2(std::string);
/*
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
*/
}


