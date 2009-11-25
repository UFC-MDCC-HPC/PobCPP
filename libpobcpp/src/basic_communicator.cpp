#include "basic_communicator.h"

namespace Pobcpp {

Basic_Communicator::Basic_Communicator() : Communicator<Basic_Communicator>()  { }

Basic_Communicator::~Basic_Communicator() { }


void Basic_Communicator::env_setted() {
	env->set_my_rank(world.rank());
}


}


