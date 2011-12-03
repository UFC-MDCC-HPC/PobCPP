#include "group.h"

namespace Pobcpp {

Group::~Group() {
//	MPI_Group_free(&group);
}

Group Group::include(int n, int *ranks) {
	MPI_Group newgroup;
	MPI_Group_incl(group, n, ranks, &newgroup);
	return Group(newgroup);
}

Group Group::exclude(int n, int *ranks) {
	MPI_Group newgroup;
	MPI_Group_excl(group, n, ranks, &newgroup);
	return Group(newgroup);
}

MPI_Group Group::get_mpi_group() {
	return group;
}


}
