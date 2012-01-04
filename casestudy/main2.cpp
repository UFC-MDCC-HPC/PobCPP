#include <iostream>
#include "integrator_main.h.pob"
int main(int argc, char** argv) { 
	pob_init;
	int it_max = 5;
	double tol = 0.000001;

	int dim_num = 3;
	int dim_partition_size = 2;
	int number_of_partitions = 8;

	int size = world.size() - 1;
	int i = world.rank() - 1;
	std::cout << "Createing Peer(" << i << "," << size << ")" << std::endl;
	IntegratorMain::Peer peer(i, size);
	peer.main(it_max, tol, dim_num, dim_partition_size, number_of_partitions);

	MPI_Finalize();
	return 0;
}
