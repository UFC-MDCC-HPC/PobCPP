#ifndef __PARALLEL_OBJECT_H__
#define __PARALLEL_OBJECT_H__

#include <map>

#include "environment.h"
#include "basic_communicator.h"

namespace Pobcpp {

class Parallel_Object {
protected:
	Parallel_Object(void);     
	virtual ~Parallel_Object(void);     

	virtual int main(void) = 0;

	Environment env;
	static Basic_Communicator comm;
};

}

#endif

