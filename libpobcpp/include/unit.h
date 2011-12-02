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
	template<typename AskedType>
	unsigned int ranksof_(Basic_Communicator& comm, int*& array, Unit_Type unit_type);
	template<typename AskedType>
	int rankof_(Basic_Communicator& comm, Unit_Type unit_type);

  unsigned int ranksof_impl(Basic_Communicator& comm, int*& array, Unit_Type& asked_type, Unit_Type& unit_type);
  int rankof_impl(Basic_Communicator& comm, Unit_Type& asked_type, Unit_Type& unit_type);
public:
	Basic_Communicator* comm; //FIXME
private:
	// No copy allowed.
	Unit(const Unit&);
	//operator=(const Unit&);
};

template<typename AskedType>
unsigned int Unit::ranksof_(Basic_Communicator& comm, int*& array, Unit_Type unit_type) {
	AskedType* asked = 0;
	Unit_Type asked_type(asked);
	return ranksof_impl(comm, array, asked_type, unit_type);
}

template<typename AskedType>
int Unit::rankof_(Basic_Communicator& comm, Unit_Type unit_type) {
	AskedType* asked = 0;
	Unit_Type asked_type(asked);
	return rankof_impl(comm, asked_type, unit_type);
}

}

#endif

