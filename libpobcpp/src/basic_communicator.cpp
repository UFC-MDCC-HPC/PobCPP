#include "basic_communicator.h"
#include "communication.h"
#include <boost/mpi/collectives.hpp>
#include <iostream>
#include <algorithm>
#include <mpi.h>
#include <typeinfo>

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
void Basic_Communicator::reduce(const datatype& in_value, datatype& out_value, MPI_Op op, int root) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(op == MPI_SUM) \
			return boost::mpi::reduce(world, in_value, out_value, std::plus<datatype>(), root); \
	if(op == MPI_MAX) \
			return boost::mpi::reduce(world, in_value, out_value, boost::mpi::maximum<datatype>(), root); \
	if(op == MPI_MIN) \
			return boost::mpi::reduce(world, in_value, out_value, boost::mpi::minimum<datatype>(), root); \
}

#define Basic_Communicator_reduce_impl2(datatype) \
void Basic_Communicator::reduce(const datatype* in_values, int n, datatype* out_values, MPI_Op op, int root) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(op == MPI_SUM) \
			return boost::mpi::reduce(world, in_values, n, out_values, std::plus<datatype>(), root); \
	if(op == MPI_MAX) \
			return boost::mpi::reduce(world, in_values, n, out_values, boost::mpi::maximum<datatype>(), root); \
	if(op == MPI_MIN) \
			return boost::mpi::reduce(world, in_values, n, out_values, boost::mpi::minimum<datatype>(), root); \
}

#define Basic_Communicator_reduce_impl3(datatype) \
void Basic_Communicator::reduce(const datatype* in_values, int n, MPI_Op op, int root) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(op == MPI_SUM) \
			return boost::mpi::reduce(world, in_values, n, std::plus<datatype>(), root); \
	if(op == MPI_MAX) \
			return boost::mpi::reduce(world, in_values, n, boost::mpi::maximum<datatype>(), root); \
	if(op == MPI_MIN) \
			return boost::mpi::reduce(world, in_values, n, boost::mpi::minimum<datatype>(), root); \
}

#define Basic_Communicator_allreduce_impl(datatype) \
void Basic_Communicator::allreduce(const datatype& in_value, datatype& out_value, MPI_Op op) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(op == MPI_SUM) \
			return boost::mpi::all_reduce(world, in_value, out_value, std::plus<datatype>()); \
	if(op == MPI_MAX) \
			return boost::mpi::all_reduce(world, in_value, out_value, boost::mpi::maximum<datatype>()); \
	if(op == MPI_MIN) \
			return boost::mpi::all_reduce(world, in_value, out_value, boost::mpi::minimum<datatype>()); \
}

#define Basic_Communicator_allreduce_impl2(datatype) \
void Basic_Communicator::allreduce(const datatype* in_values, int n, datatype* out_values, MPI_Op op) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	if(op == MPI_SUM) \
			return boost::mpi::all_reduce(world, in_values, n, out_values, std::plus<datatype>()); \
	if(op == MPI_MAX) \
			return boost::mpi::all_reduce(world, in_values, n, out_values, boost::mpi::maximum<datatype>()); \
	if(op == MPI_MIN) \
			return boost::mpi::all_reduce(world, in_values, n, out_values, boost::mpi::minimum<datatype>()); \
}

#define Basic_Communicator_alltoall_impl(datatype) \
void Basic_Communicator::alltoall(const datatype* in_values, datatype* out_values) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	boost::mpi::all_to_all(world, in_values, out_values); \
}

#define Basic_Communicator_alltoall_impl2(datatype) \
void Basic_Communicator::alltoall(const datatype* in_values, int n, datatype* out_values) { \
  boost::mpi::communicator world(comm, boost::mpi::comm_attach); \
	boost::mpi::all_to_all(world, in_values, n, out_values); \
}
#define Basic_Communicator_alltoallv_impl(datatype, mpi_dt) \
void Basic_Communicator::alltoall(datatype* in_values, int* sendcnts, int* sdispls, datatype* out_values, int* recvcnts, int* rdispls) { \
	MPI_Alltoallv(in_values, sendcnts, sdispls, mpi_dt, out_values, recvcnts, rdispls, mpi_dt, comm); \
}

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

void Basic_Communicator::barrier() const {
	boost::mpi::communicator world(comm, boost::mpi::comm_attach);
	return world.barrier();
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

Basic_Communicator_reduce_impl3(int);
Basic_Communicator_reduce_impl3(unsigned int);
Basic_Communicator_reduce_impl3(float);
Basic_Communicator_reduce_impl3(double);
Basic_Communicator_reduce_impl3(char);
Basic_Communicator_reduce_impl3(std::string);

Basic_Communicator_allreduce_impl(int);
Basic_Communicator_allreduce_impl(unsigned int);
Basic_Communicator_allreduce_impl(float);
Basic_Communicator_allreduce_impl(double);
Basic_Communicator_allreduce_impl(char);
Basic_Communicator_allreduce_impl(std::string);

Basic_Communicator_allreduce_impl2(int);
Basic_Communicator_allreduce_impl2(unsigned int);
Basic_Communicator_allreduce_impl2(float);
Basic_Communicator_allreduce_impl2(double);
Basic_Communicator_allreduce_impl2(char);
Basic_Communicator_allreduce_impl2(std::string);

Basic_Communicator_alltoall_impl(int);
Basic_Communicator_alltoall_impl(unsigned int);
Basic_Communicator_alltoall_impl(float);
Basic_Communicator_alltoall_impl(double);
Basic_Communicator_alltoall_impl(char);
Basic_Communicator_alltoall_impl(std::string);

Basic_Communicator_alltoall_impl2(int);
Basic_Communicator_alltoall_impl2(unsigned int);
Basic_Communicator_alltoall_impl2(float);
Basic_Communicator_alltoall_impl2(double);
Basic_Communicator_alltoall_impl2(char);
Basic_Communicator_alltoall_impl2(std::string);

Basic_Communicator_alltoallv_impl(int, MPI_INT);
/*Basic_Communicator_alltoallv_impl(unsigned int, MPI_UINT);
Basic_Communicator_alltoallv_impl(float, MPI_FLOAT);
Basic_Communicator_alltoallv_impl(double, MPI_DOUBLE);
Basic_Communicator_alltoallv_impl(char, MPI_CHAR);*/

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


