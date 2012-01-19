#include <iostream>
#include "integrator_main.pob.h"
int main(int argc, char** argv) { 
	MPI_Init(&argc, &argv);
	Communicator world;
	if(world.size() == 1) {
		std::cerr << ">1 process please." << std::endl;
		return 1;
	}
	if(world.rank() == 0) {
		int dim_num = 6;
		int dim_partition_size = 2;
		int number_of_partitions = 8;
		int size = world.size() - 1;
		IntegratorMain::Root root;
		root.main(dim_num, dim_partition_size, number_of_partitions, size);
		MPI_Finalize();
		return 0;
	}
	else {
		int it_max = 5;
		double tol = 0.000001;

		int dim_num = 6;
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
}
