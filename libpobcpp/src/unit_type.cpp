#include "unit_type.h"

namespace Pobcpp {

Unit_Type::Unit_Type() : unit_type() { }

Unit_Type::Unit_Type(const char* _unit_type) : unit_type(std::string(_unit_type)) { }

Unit_Type::~Unit_Type() { }

bool Unit_Type::operator==(const Unit_Type& _unit_type) const {
	if(unit_type == _unit_type.unit_type)
		return true;
	else
		return false;
}

bool Unit_Type::operator<(const Unit_Type& _unit_type) const {
	if(unit_type < _unit_type.unit_type)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& ostream, const Unit_Type& _unit_type) {
	ostream << _unit_type.unit_type;
	return ostream;
}

}


