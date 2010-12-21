#ifndef __CREATE_UNIT__
#define __CREATE_UNIT__

//#include <boost/mpi/environment.hpp>
#include <map> //std::pair
#include "unit.h"
#include "unit_type.h"
#include "environment.h"

bool is_no_unit(const Pobcpp::Unit_Type& unit_type);
void create_unit_impl(Pobcpp::Unit* _created_unit, std::pair<unsigned int, unsigned int> _enums, Pobcpp::Pob_Type_Array& typearray, Pobcpp::Unit_Type& unit_type) { }
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

template<typename TypePObject, typename TypeUnit>
void create_unit(TypeUnit* _created_unit, std::pair<unsigned int, unsigned int> _enums) {
	Pobcpp::Pob_Type_Array typearray =  TypePObject::__get_types(); // POb units.
	Pobcpp::Unit_Type unit_type(_created_unit);
	create_unit_impl(_created_unit, _enums, typearray, unit_type);
}

#endif

