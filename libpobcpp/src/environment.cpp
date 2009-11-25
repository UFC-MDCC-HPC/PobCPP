#include "environment.h"
#include "communication.h"

#include <boost/serialization/map.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

namespace Pobcpp {

Environment::Environment(void) : my_rank(-1) { }

Environment::~Environment(void) { }


void Environment::set_my_rank(const Rank& _rank) {
	my_rank = _rank;
}

Rank Environment::get_rank (const Unit_Type& _unit_type) {
	return units_rank[_unit_type]; 
}

void Environment::init(void) {
	decide_ranks();
	execute_main();
}

void Environment::decide_ranks(void) {
	/**
	 * TODO: check if my_rank is -1 and raise an exception
	 * FIXME: Remove MPI and use comm or just create an MPI_Environment and a
	 * Environment base class. 
	 */
	if(my_rank == 0) {
		boost::mpi::communicator world;
		int rank = 0;
		if(!units_rank.empty()) {
			std::map<Unit_Type, Rank>::iterator it = units_rank.begin();
			for(int i = 0;i < world.size() and it != units_rank.end() ;i++) {
				std::cout << "==" << world.rank() << "==" << "Decidindo que a unidade " << (*it).first << " ira ficar com o rank "  << rank << std::endl;
				units_rank[(*it).first] = rank++;
				it++;
			}
		}
		for(int i =0; i < world.size();i++) {
			world.send(i, 1, units_rank); //1 = TAG_ENVIRONMENT
		}
	}
	else {
		boost::mpi::communicator world;
		std::cout << "==" << world.rank() << "==" << " Waiting configuration" << std::endl;
		std::map<Unit_Type, Rank> units_;
		std::cout << "==" << world.rank() << "==" << " Configuration received: Unit" << std::endl;
		world.recv(0, 1, units_); //1 = TAG_ENVIRONMENT
		std::map<Unit_Type, Rank>::iterator it;
		for(it = units_.begin(); it != units_.end(); it++) {
			std::cout << "==" << world.rank() << "==" << "Foi decidido que a unidade " << (*it).first << " ira ficar com o rank "  << (*it).second << std::endl;
		}
		units_rank = units_;
	}
}

void Environment::execute_main(void) {
	
	for(std::map<Unit_Type, Rank>::iterator it = units_rank.begin();it != units_rank.end() ;it++) {
		Unit* unit = units[(*it).first];
		if(my_rank == (*it).second) {
			unit->set_global_rank(my_rank);
			unit->main();
		}
		else 
			delete unit;
	}
}

}

