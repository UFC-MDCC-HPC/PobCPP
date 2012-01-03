#include <iostream>
#include "integrator_main.h.pob"
int main(int argc, char** argv) { 
	int dim_num = 3;
	int dim_partition_size = 2;
	int number_of_partitions = 8;

	int size = world.size() - 1;
	IntegratorMain::Root root;
	create_unit<IntegratorMain>(&root);
	root.main(dim_num, dim_partition_size, number_of_partitions, size);
	
	MPI_Finalize();
	return 0;
}
