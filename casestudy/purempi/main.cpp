#include <boost/mpi.hpp>
#include <iostream>
#include "nintlib/nintlib.H"
#include <cmath>
namespace mpi = boost::mpi;

int main(int argc, char* argv[]) {
	mpi::environment env(argc, argv);
	mpi::communicator world;
	const int TAG_A = 1000;
	const int TAG_B = 2000;
	const int TAG_RESULT = 3000;

	int it_max = 2;
	int ind = 0;
	double tol = 0.000001;

	int dim_num = 1;
	int dim_partition_size = 1;
	int number_of_partitions = 1;

	double* result;
	int* sub_num;
	
	int rank = world.rank();
	int size = world.size() - 1; // Workers

	int num_jobs = (int)std::pow(dim_partition_size, dim_num);
	int num_local_jobs = num_jobs / size;

	if(rank == 0) {
		double* a = new double[(size +1) * 
		double*** a = new double**[size + 1];
		double*** b = new double**[size + 1];
		for(unsigned int i = 0; i < size + 1; ++i) {
			a[i] = new double*[num_local_jobs];
			b[i] = new double*[num_local_jobs];
			for(unsigned int j = 0; j < num_local_jobs; ++j) {
				a[i][j] = new double*[dim_num];
				b[i][j] = new double*[dim_num];

			}
		}
		int dims* = new int[dim_num];
		for (int job = 0; job < num_jobs; job++) {
			int r = job % size + 1;
			int j = job / size;
			for (int i = 0; i < dim_num; i++) {
				a[r][j][i] = dims[i] * (1.0 / dim_partition_size);
				b[r][j][i] = (dims[i] + 1) * (1.0 / dim_partition_size);
			}

			// NEXT JOB
			int ii = 0;
			while (ii < dim_num) {
				dims[ii] = (dims[ii] + 1) % dim_partition_size;
				if (dims[ii] == 0)
    				ii++;
				else
					break;
			}
		}
		// Distribute jobs.

		mpi::scatter(a, 0);
		mpi::scatter(b, 0);
		// Collect/Combine results

	}

}
