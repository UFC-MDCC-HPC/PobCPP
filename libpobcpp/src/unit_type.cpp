#include "unit_type.h"

namespace Pobcpp {

Unit_Type::Unit_Type() : unit_type(), enumerators(0) { }

Unit_Type::~Unit_Type() { }

bool Unit_Type::operator==(const Unit_Type& _unit_type) const {
	if(unit_type == _unit_type.unit_type 
			&& enumerators == _unit_type.enumerators
		//	&& enums.first == _unit_type.enums.first)
		//	&& enums.second == _unit_type.enums.second)
			)
		return true;
	else
		return false;
}

bool Unit_Type::operator<(const Unit_Type& _unit_type) const {
	if(!has_enumerators()) {
		if(unit_type < _unit_type.unit_type) 
			return true;
		else
			return false;
	} else {
		if(unit_type < _unit_type.unit_type) {
			return true;
		}
		else if (unit_type == _unit_type.unit_type) {
			if(enums.first < _unit_type.enums.first)
				return true;
			else 
				return false;
		}
		else 
			return false;
	}
}

std::ostream& operator<<(std::ostream& ostream, const Unit_Type& _unit_type) {
	ostream << _unit_type.unit_type;
	return ostream;
}

}


