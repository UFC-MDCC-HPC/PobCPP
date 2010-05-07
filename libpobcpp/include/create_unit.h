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

bool is_no_unit(const Pobcpp::Unit_Type& unit_type) {
	Pobcpp::No_Unit* no_unit;
	if(unit_type == Pobcpp::Unit_Type(no_unit))
		return true;
	return false;
}

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit, std::pair<unsigned int, unsigned int> = std::make_pair(0,0));

template<typename TypePObject>
void create_unit() {
	Pobcpp::No_Unit* nounit = 0;
	create_unit<TypePObject>(nounit);
}

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit, unsigned int i, unsigned int n) {
	create_unit<TypePObject>(_created_unit, std::make_pair(i,n));
}

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit, std::pair<unsigned int, unsigned int>) {
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
	Pobcpp::Environment* env = new Pobcpp::Environment();
//	if(!(unit_type == Pobcpp::Unit_Type(no_unit)))
//		env->add(unit_type, rank);	
	int* ranks = new int[typearray.size()];
	for(unsigned int i = 0; i < types.size(); i++) {
		for(unsigned int j = 0; j < typearray.size(); j++) {
			if(types.at(i).first == typearray.get_type(j)) {
				check++;
	//			env->add(types.at(i).first, types.at(i).second);
				ranks[i] = types.at(i).second;
			}
		}
	}
	for(unsigned int i = 0; i < typearray.size(); i++)
		std::cout << "==" << unit_type << "== - " << ranks[i] << " ";
	std::cout << std::endl;
	if(check == typearray.size()) {
		// Creating new intracommunicator
		MPI_Group orig_group, new_group;
		MPI_Comm comm;
		MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
		MPI_Group_incl(orig_group, typearray.size(), ranks, &new_group);
		MPI_Comm_create(MPI_COMM_WORLD, new_group, &comm);
		if(!is_no_unit(unit_type)) {
			boost::mpi::communicator bcomm(comm, boost::mpi::comm_attach);
			std::cout << "Comm create "<< std::endl;			
			int inew_rank = -1;
			MPI_Group_rank (new_group, &inew_rank); 
			std::cout << "New rank true - " << inew_rank << std::endl;			
			unsigned int new_rank = bcomm.rank();
			std::cout << "New rank " << bcomm.rank() << std::endl;			
			all_gather(bcomm, std::make_pair(unit_type, new_rank), types); // send the pair<unit_type,world.rank()>
			std::cout << unit_type << "All_gather "<< std::endl;			
			for(unsigned int i = 0; i < types.size(); i++)
				env->add(types.at(i).first, types.at(i).second);
			env->add(unit_type, new_rank);	
		}

		if(_created_unit) {
			_created_unit->comm->set_intracomm(comm);
			_created_unit->comm->set_environment(env);
			env->set_complete();
			// FIXME: Ranks need to be updated to new comm.
		}
	}
	// Construct comm object with MPI_IntraCommunicator
}

#endif

