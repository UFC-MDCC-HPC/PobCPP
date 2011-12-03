#ifndef __GROUP__
#define __GROUP__

#include "mpi.h"

namespace Pobcpp {

class Group {
public:
	Group(const Group& _group) : group(_group.group) { }
	Group(MPI_Group _group) : group(_group) { }
	~Group();

	 Group include(int n, int *ranks);
	 Group exclude(int n, int* ranks);

	 MPI_Group get_mpi_group();

private:
	MPI_Group group;
//	Group(MPI_Group _group) : group(_group) { }
};

}


#endif

