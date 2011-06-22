#ifndef __UNIT__
#define __UNIT__

#include "basic_communicator.h"
#include "unit_type.h"
namespace Pobcpp {
class Basic_Communicator;
class Unit {
protected:

	/**
   * Default constructor.
   */
	Unit();

	/** 
	 * Destructor
	 */
	virtual ~Unit();
	template<typename UnitType>
	unsigned int* ranksof_(Basic_Communicator comm, Unit_Type& unit_type);
	unsigned int* ranksof_impl(Basic_Communicator comm, Unit_Type& asked_type, Unit_Type& unit_type);
public:
	Basic_Communicator* comm; //FIXME
private:
	// No copy allowed.
	Unit(const Unit&);
	//operator=(const Unit&);
};

template<typename UnitType>
unsigned int* Unit::ranksof_(Basic_Communicator comm, Unit_Type& unit_type) {
	UnitType* asked;
	Unit_Type asked_type(asked);
	return ranksof_impl(comm, asked_type, unit_type);
}

}

#endif

