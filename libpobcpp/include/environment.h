#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "rank.h"
#include "unit_type.h"
#include "unit.h"

#include <map> //std::pair
#include <string>

namespace Pobcpp {

class Environment {
public:
	Environment (void);
	~Environment (void);

	void set_my_rank (const Rank& _rank);

	template<typename Type>
	void add();

	Rank get_rank (const Unit_Type& _unit_type);

	void init (void);
	
private:
	void decide_ranks();
	void execute_main();

	Rank my_rank;
	std::map<Unit_Type, Rank> units_rank;
	std::map<Unit_Type, Unit*> units;
};

template<typename Type>
void Environment::add() {
	Type* unit = new Type();
	Unit_Type unit_type(typeid(unit).name());	
	units_rank[unit_type] = Rank();
	units[unit_type] = unit;
}

}

#endif

