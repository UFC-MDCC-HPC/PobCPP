#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/group.hpp>
#include <boost/serialization/map.hpp> //std::pair serialize
#include "unit_type_serialization.h"
#include "unit.h"
#include "create_unit.h"
bool is_no_unit(const Pobcpp::Unit_Type& unit_type) {
	Pobcpp::No_Unit* no_unit;
	if(unit_type == Pobcpp::Unit_Type(no_unit))
		return true;
	return false;
}

void create_unit_impl(Pobcpp::Unit* _created_unit, std::pair<unsigned int, unsigned int> _enums, Pobcpp::Pob_Type_Array& typearray, Pobcpp::Unit_Type& unit_type) {
	/*boost::mpi::communicator world;
	boost::mpi::group wgroup = world.group();
	boost::mpi::group group;
	unsigned int rank = world.rank();
	unsigned int enum_i = _enums.first;
	unsigned int enum_n = _enums.second;
	Enum_Checker enum_checker;
	for(unsigned int i = 0; i < typearray.size(); i++) {
		if(typearray.get_type(i).has_enumerators()) {
			enum_checker.add(typearray.get_type(i));
		}
	}
	//enum
	if(enum_n > 0) {
//		unit_type.set_enums(_enums);
		unit_type.set_enumerators(1); // FIXME
	}
	// Exchange with others units, each rank.
	std::vector<Unit_Type_Pack> types;
	all_gather(world, Unit_Type_Pack(unit_type, _enums, rank), types); // send the pair<unit_type,world.rank()>

	// Check if every type is ok.
	unsigned int check = 0;
	std::vector<int> temp_ranks;
	for(unsigned int i = 0; i < types.size(); i++) {
		for(unsigned int j = 0; j < typearray.size(); j++) {
			if(!types.at(i).unit_type.has_enumerators()) {
				if(types.at(i).unit_type == typearray.get_type(j)) {
					check++;
					temp_ranks.push_back(types.at(i).rank);
				}
			} else {
				if(types.at(i).unit_type == typearray.get_type(j)) {
					if(enum_checker.check(types.at(i).unit_type, types.at(i).enums.second)) {
						temp_ranks.push_back(types.at(i).rank);
					}
				}
			}
		}
	}
	check += enum_checker.check();
	if(check == typearray.size()) {
		// Creating new intracommunicator
		MPI_Group orig_group, new_group;
		MPI_Comm comm;
		MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
//		std::cout << "Creating a group with " << temp_ranks.size() << " members." << std::endl;
//		MPI_Group_incl(orig_group, temp_ranks.size(), ranks, &new_group);
		MPI_Group_incl(orig_group, temp_ranks.size(), &(temp_ranks.front()), &new_group);
		MPI_Comm_create(MPI_COMM_WORLD, new_group, &comm);
		// Time to set Environment.
		if(!is_no_unit(unit_type)) {
			Pobcpp::Environment* env = new Pobcpp::Environment();
			boost::mpi::communicator bcomm(comm, boost::mpi::comm_attach);
			int inew_rank = -1;
			MPI_Group_rank (new_group, &inew_rank); 
			unsigned int new_rank = bcomm.rank();
			unit_type.set_enums(_enums);
//			std::cout << "==" << unit_type << " == novo rank: " << new_rank << std::endl;
			all_gather(bcomm, Unit_Type_Pack(unit_type, _enums, new_rank), types); // send the pair<unit_type,world.rank()>
			for(unsigned int i = 0; i < types.size(); i++)
				env->add(types.at(i).unit_type, types.at(i).rank);
//			env->add(unit_type, new_rank);	
			_created_unit->comm->set_intracomm(comm);
			_created_unit->comm->set_environment(env);
			env->set_complete();
		}
	} else {
		std::cerr << "Error while instantiting Parallel Object named: " << unit_type << " (Debugging information: Check: " << check << " and typesize: " << typearray.size() << ")" <<  std::endl;
	}*/
}



