#include "unit.h"

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

namespace Pobcpp {

Unit::Unit (void) : global_rank (-1) { }

Unit::Unit (int _global_rank) : global_rank (_global_rank) { }

Unit::~Unit (void) { }

int Unit::get_global_rank (void) const {
    return global_rank;
}

void Unit::set_global_rank (int _global_rank) {
    global_rank = _global_rank;    
}



}

