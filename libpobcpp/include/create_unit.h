#ifndef __CREATE_UNIT__
#define __CREATE_UNIT__


#include <boost/mpi/communicator.hpp>
#include <boost/mpi/group.hpp>
//#include <boost/mpi/environment.hpp>
#include <map> //std::pair
#include <boost/serialization/map.hpp> //std::pair serialize

#include "unit_type.h"

namespace Pobcpp {
	class No_Unit : public Pobcpp::Unit { };
}

template<class ParallelObject, class TypeUnit>
void create_unit(TypeUnit* _created_unit);

template<typename TypePObject>
void create_unit() {
	Pobcpp::No_Unit* nounit = 0;
	create_unit<TypePObject>(nounit);
}

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit) {
	boost::mpi::communicator world;
	boost::mpi::group wgroup = world.group();
	boost::mpi::group group;
	unsigned int rank = world.rank();

	Pobcpp::Pob_Type_Array typearray =  TypePObject::__get_types(); // POb units.
	Pobcpp::Unit_Type unit_type(_created_unit);

	// Exchange with others units, each rank.
	std::vector<std::pair<Pobcpp::Unit_Type, unsigned int> > types;
	all_gather(world, std::make_pair(unit_type, rank), types); // send the pair<unit_type,world.rank()>

	// Check if every type is ok.
	unsigned int check = 0;
//	std::vector<unsigned int> ranks;
	Pobcpp::Environment* env = new Pobcpp::Environment();
	Pobcpp::No_Unit* no_unit;
	if(!(unit_type == Pobcpp::Unit_Type(no_unit)))
		env->add(unit_type, rank);	
	int* ranks = new int[typearray.size()];
	for(unsigned int i = 0; i < types.size(); i++) {
		for(unsigned int j = 0; j < typearray.size(); j++) {
			if(types.at(i).first == typearray.get_type(j)) {
				check++;
				env->add(types.at(i).first, types.at(i).second);
//				ranks.push_back(types.at(i).second);
				ranks[i] = types.at(i).second;
//				std::cout << "==" << world.rank() << "==" << "Rank " << ranks[i] << " set." << std::endl;
			}
		}
	}
	if(check == typearray.size()) {
//		std::cout << "Creating group "<< std::endl;
		// Creating new intracommunicator
		MPI_Group orig_group, new_group;
		MPI_Comm comm;
		MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
	//	std::cout << "Incl group "<< std::endl;
		MPI_Group_incl(orig_group, typearray.size(), ranks, &new_group);
	//	std::cout << "Comm create "<< std::endl;
		MPI_Comm_create(MPI_COMM_WORLD, new_group, &comm);
		if(_created_unit) {
			_created_unit->comm->set_intracomm(comm);
			_created_unit->comm->set_environment(env);
			env->set_complete();
		}
		//std::cout << "==" << world.rank() << "==" << "Unit created "<< std::endl;
	}
	// Construct comm object with MPI_IntraCommunicator
}

#endif

