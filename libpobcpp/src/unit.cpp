#include "unit.h"

#include "unit_type_serialization.h"
#include "basic_communicator.h"
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/group.hpp>
#include <boost/serialization/map.hpp> //std::pair serialize
#include <boost/mpi/environment.hpp>

namespace Pobcpp {

Unit::Unit (void) { 
	comm = new Basic_Communicator;
}

Unit::~Unit (void) { }

unsigned int Unit::ranksof_impl(Basic_Communicator& comm, int*& array, Unit_Type& asked_type, Unit_Type& unit_type) {
// Constructing the array.
	boost::mpi::communicator world(comm.get_mpi_comm(), boost::mpi::comm_attach);
	unsigned int rank = world.rank();

	std::vector<Unit_Type_Pack> types;
	all_gather(world, Unit_Type_Pack(unit_type, rank), types); // send the pair<unit_type,world.rank()>
	unsigned int size = 0;
	std::vector<unsigned int> ranks;
	for(int i = 0; i < world.size(); ++i) {
		Unit_Type_Pack pack_i = types[i];
		unsigned int ranki = pack_i.rank;
		Unit_Type typei = pack_i.unit_type;
		if(asked_type == typei) {
			ranks.push_back(ranki);
			size++;
		}
	}
	array = new int[size];
	memcpy(array, &(ranks[0]), size * sizeof(unsigned int));
	return size;
}

int Unit::rankof_impl(Basic_Communicator& comm, Unit_Type& asked_type, Unit_Type& unit_type) {
	boost::mpi::communicator world(comm.get_mpi_comm(), boost::mpi::comm_attach);
	unsigned int rank = world.rank();
	unsigned int result = 0;

	std::vector<Unit_Type_Pack> types;
	all_gather(world, Unit_Type_Pack(unit_type, rank), types); // send the pair<unit_type,world.rank()>
	unsigned int size = 0;
	for(int i = 0; i < world.size(); ++i) {
		Unit_Type_Pack pack_i = types[i];
		unsigned int ranki = pack_i.rank;
		Unit_Type typei = pack_i.unit_type;
		if(asked_type == typei) {
      result = ranki;	
			size++;
		}
	}
	if(size == 0)
		return -1; // not found
	else if(size == 1)
		return result;
	else 
		return -1; // single unit duplicated
}

}
