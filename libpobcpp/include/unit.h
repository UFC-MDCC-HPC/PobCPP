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
public: //FIXME 
	Basic_Communicator* comm;
private:
	Unit(const Unit&);
	//operator=(const Unit&);
};

}

#endif

