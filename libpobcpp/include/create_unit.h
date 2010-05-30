#ifndef __CREATE_UNIT__
#define __CREATE_UNIT__

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/group.hpp>
//#include <boost/mpi/environment.hpp>
#include <map> //std::pair
#include <boost/serialization/map.hpp> //std::pair serialize
#include "unit.h"
#include "unit_type.h"

bool is_no_unit(const Pobcpp::Unit_Type& unit_type);
namespace Pobcpp {
	class No_Unit : public Pobcpp::Unit { };
}
class Enum_Checker {
public:
	Enum_Checker() : checking(0) { }

	void add(const Pobcpp::Unit_Type& _unit_type) {
		types[_unit_type] = std::make_pair(0, -1);
	}

	bool check(const Pobcpp::Unit_Type& _unit_type, unsigned int _enum_n) {
		//unsigned int _enum_i = _unit_type.get_enums().first;
		if(types.count(_unit_type) == 0) {
//			std::cout << "lascou pq não tem ninguem" << std::endl;
			return false;
		}
		std::pair<unsigned int, int> current_pair = types[_unit_type];
//		std::cout << "current pair 1 - " << current_pair.first << std::endl;
		if(current_pair.second == -1) {
			current_pair.second = _enum_n;
			current_pair.first = _enum_n;
		} else if((unsigned int) current_pair.second != _enum_n) {
			return false;
		}
		if(current_pair.first == 0) {
			return false;
		}
		current_pair.first--;
		types[_unit_type] = current_pair;
		if(current_pair.first == 0)
			checking++;
		return true;
	}

	int check(void) const {
			return checking;
	}

private:
	unsigned int checking;
	std::map<Pobcpp::Unit_Type, std::pair<int, int> > types;
};


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

struct Unit_Type_Pack {
	Unit_Type_Pack(Pobcpp::Unit_Type unit_type,
	               std::pair<unsigned int, unsigned int> enums,
								 unsigned int rank) :
	               unit_type(unit_type),
								 enums(enums),
								 rank(rank) { }
	Unit_Type_Pack() { }
	Pobcpp::Unit_Type unit_type;
	std::pair<unsigned int, unsigned int> enums;
	unsigned int rank;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & unit_type;
		ar & rank;
		ar & enums;
	}

};

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit, std::pair<unsigned int, unsigned int> _enums) {
	boost::mpi::communicator world;
	boost::mpi::group wgroup = world.group();
	boost::mpi::group group;
	unsigned int rank = world.rank();
	unsigned int enum_i = _enums.first;
	unsigned int enum_n = _enums.second;
	Enum_Checker enum_checker;
	Pobcpp::Pob_Type_Array typearray =  TypePObject::__get_types(); // POb units.
	for(unsigned int i = 0; i < typearray.size(); i++) {
		if(typearray.get_type(i).has_enumerators()) {
			enum_checker.add(typearray.get_type(i));
		}
	}
	Pobcpp::Unit_Type unit_type(_created_unit);
//	std::cout << "==" << unit_type << "== Meu rank inicial é: " << rank << std::endl;
	//enum
	if(enum_n != 0) {
//		unit_type.set_enums(_enums);
		unit_type.set_enumerators(1);
	}
	// Exchange with others units, each rank.
//	std::vector<std::pair<Pobcpp::Unit_Type, unsigned int> > types;
//	typedef std::pair<Pobcpp::Unit_Type, std::pair<unsigned int, unsigned int> > Type_and_Enum;
	//std::vector<std::pair< std::pair<Pobcpp::Unit_Type, std::pair<unsigned int, unsigned int> > , unsigned int> > types;
	std::vector<Unit_Type_Pack> types;
	all_gather(world, Unit_Type_Pack(unit_type, _enums, rank), types); // send the pair<unit_type,world.rank()>

	// Check if every type is ok.
	unsigned int check = 0;
	std::vector<unsigned int> temp_ranks;
	for(unsigned int i = 0; i < types.size(); i++) {
		for(unsigned int j = 0; j < typearray.size(); j++) {
			if(!types.at(i).unit_type.has_enumerators()) {
				if(types.at(i).unit_type == typearray.get_type(j)) {
		//			std::cout << "==" << unit_type <<"== Reco this type: " << types.at(i).unit_type << std::endl;
					check++;
					temp_ranks.push_back(types.at(i).rank);
				}
			} else {
				if(types.at(i).unit_type == typearray.get_type(j)) {
					if(enum_checker.check(types.at(i).unit_type, types.at(i).enums.second)) {
			//			std::cout << "==" << unit_type <<"== Reco this ENUM type: " << types.at(i).unit_type << std::endl;
						temp_ranks.push_back(types.at(i).rank);
					}
				}
			}
		}
	}
	check += enum_checker.check();
	int* ranks = new int[temp_ranks.size()];
	//std::cout << "Temp ranks size" << temp_ranks.size() << std::endl;
	for(unsigned int i = 0; i < temp_ranks.size(); i++) {
		ranks[i] = temp_ranks[i];
		//std::cout << "==" << unit_type <<"== Rank:: " << ranks[i] << std::endl;
	}
//	std::cout << "==" << unit_type <<"== My check value is: " << check << " and typearray.size is " << typearray.size() << std::endl;
	if(check == typearray.size()) {
		// Creating new intracommunicator
		MPI_Group orig_group, new_group;
		MPI_Comm comm;
		MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
		MPI_Group_incl(orig_group, temp_ranks.size(), ranks, &new_group);
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
		TypePObject* a;
		std::cerr << "Error while instantiting POb(" << Pobcpp::Unit_Type(a) << ")! Check: " << check << " and typesize: " << typearray.size() << std::endl;
	}
}
#endif

