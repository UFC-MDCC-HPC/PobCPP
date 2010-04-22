#include "environment.h"

namespace Pobcpp {

Environment::Environment(void) : complete(false), my_rank(0) { }

Environment::~Environment(void) { }


void Environment::set_my_rank(const unsigned int& _rank) {
	my_rank = _rank;
}

unsigned int Environment::get_rank (const Unit_Type& _unit_type) {
	return units_rank[_unit_type]; 
}

void Environment::add(const Unit_Type& _unit_type, const unsigned int& rank) {
	units_rank[_unit_type] = rank;
}

void Environment::set_complete() { 
	complete = true;
}

bool Environment::isComplete() const {
	return complete;
}


}

