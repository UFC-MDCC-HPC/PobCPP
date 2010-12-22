#ifndef __UNIT__
#define __UNIT__

#include "basic_communicator.h"

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
public:
	Basic_Communicator* comm; //FIXME
private:
	// No copy allowed.
	Unit(const Unit&);
	//operator=(const Unit&);
};

}

#endif

