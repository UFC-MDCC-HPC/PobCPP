#include "parallel_object.h"
#include "communication.h"

namespace Pobcpp {

Basic_Communicator Parallel_Object::comm;

Parallel_Object::Parallel_Object(void) : env() {
	comm.set_environment(&env);
}

Parallel_Object::~Parallel_Object(void) { }

}

