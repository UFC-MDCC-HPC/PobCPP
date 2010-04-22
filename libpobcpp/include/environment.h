#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "rank.h"
#include "unit_type.h"

#include <map> //std::pair
#include <string>

namespace Pobcpp {

class Environment {
public:
	Environment (void);
	~Environment (void);

	void set_my_rank (const unsigned int& rank);

	void add(const Unit_Type& _unit_type, const unsigned int& rank);

	unsigned int get_rank (const Unit_Type& _unit_type);

	void set_complete();
	bool isComplete() const;
	
private:
	bool complete;
	unsigned int my_rank;
	std::map<Unit_Type, unsigned int> units_rank;
};


}

#endif

