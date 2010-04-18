#ifndef __UNIT__
#define __UNIT__

#include <typeinfo>

#include "unit_type.h"
#include <iostream>

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
   
private:
		Basic_Communicator* comm;
};

}

#endif

