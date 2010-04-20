#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

#include "unit_type.h"

template<class ParallelObject, class Unit>
void create_unit(Unit* _created_unit);

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit) {
	boost::mpi::communicator world;

	// Exchange with others units, each rank.
	TypeUnit* typeunit;
	Pobcpp::Unit_Type unit_type(typeid(typeunit).name());
	std::vector<Pobcpp::Unit_Type> types;
	all_gather(world, unit_type, types); // send the tuple<unit_type,world.rank()>
	for(unsigned int i = 0; i < types.size(); i++) {
		std::cout << "Tipo: " << unit_type << std::endl;
	}
	// Check if everybody is ok
	// Construct Environment and
	// Construct comm object with MPI_IntraCommunicator
}
