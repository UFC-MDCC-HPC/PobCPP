#include <iostream>
#include "integrator_main.pob.h"
int main(int argc, char** argv) { 
	MPI_Init(&argc, &argv);
	int dim_num = 6;
	int dim_partition_size = 2;
	int number_of_partitions = 8;
	Communicator world;
	int size = world.size() - 1;
	IntegratorMain::Root root;
	root.main(dim_num, dim_partition_size, number_of_partitions, size);
	
	MPI_Finalize();
	return 0;
}
