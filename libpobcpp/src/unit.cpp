#include "unit.h"

#include "basic_communicator.h"
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

namespace Pobcpp {

Unit::Unit (void) { 
	comm = new Basic_Communicator;
}

Unit::~Unit (void) { }

}

