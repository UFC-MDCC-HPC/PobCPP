#ifndef __CREATE_UNIT__
#define __CREATE_UNIT__


#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <map> //std::pair
#include <boost/serialization/map.hpp> //std::pair serialize

#include "unit_type.h"

template<class ParallelObject, class TypeUnit>
void create_unit(TypeUnit* _created_unit);

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit) {
	boost::mpi::communicator world;
	unsigned int rank = world.rank();

	Pobcpp::Pob_Type_Array typearray =  TypePObject::__get_types(); // POb units.
	Pobcpp::Unit_Type unit_type(_created_unit);

	// Exchange with others units, each rank.
	std::vector<std::pair<Pobcpp::Unit_Type, unsigned int> > types;
	all_gather(world, std::make_pair(unit_type, rank), types); // send the tuple<unit_type,world.rank()>

	// Check if every type is ok.
	unsigned int check = 0;
	Pobcpp::Environment* env = new Pobcpp::Environment();
	env->add(unit_type, rank);	
	for(unsigned int i = 0; i < types.size(); i++) {
		for(unsigned int j = 0; j < typearray.size(); j++) {
			if(types.at(i).first == typearray.get_type(j)) {
				check++;
				env->add(types.at(i).first, types.at(i).second);	
			}
		}
	}
	if(check == typearray.size()) {
		_created_unit->comm->set_environment(env);
		env->set_complete();
	}

	// Construct comm object with MPI_IntraCommunicator
}

#endif

