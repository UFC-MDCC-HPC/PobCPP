#include "communication.h"
#include <iostream>
#include "integrator_main.h"
#include "create_unit.h"
int main(int argc, char** argv) { 
	pob_init;
	int dim_num = 5;
	int dim_partition_size = 16;
	int number_of_partitions = 32;

	int size = world.size() - 1;
	IntegratorMain::Root root;
	create_unit<IntegratorMain>(&root);
	root.main(dim_num, dim_partition_size, number_of_partitions, size);
	
	MPI_Finalize();
	return 0;
}
