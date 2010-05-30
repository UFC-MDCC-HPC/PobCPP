#include "environment.h"

#include <iostream>

namespace Pobcpp {

Environment::Environment(void) : complete(false), my_rank(0) { }

Environment::~Environment(void) { }


void Environment::set_my_rank(const unsigned int& _rank) {
	my_rank = _rank;
}

unsigned int Environment::get_rank (const Unit_Type& _unit_type) {
	if(!units_rank.count(_unit_type))
		std::cerr << "Environment::get_rank() error. Unknown type: " << _unit_type << std::endl;
	return units_rank[_unit_type]; 
}

void Environment::add(const Unit_Type& _unit_type, const unsigned int& rank) {
	units_rank[_unit_type] = rank;
}

void Environment::set_complete() { 
	std::map<Unit_Type, unsigned int>::iterator iter;
	/*for(iter = units_rank.begin(); iter != units_rank.end(); ++iter ) {
		std::cout << "Unit_Type: " << iter->first << ", Rank: " << iter->second << std::endl;
	}	*/
	complete = true;
}

bool Environment::isComplete() const {
	return complete;
}


}

