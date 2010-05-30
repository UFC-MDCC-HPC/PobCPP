#include <boost/mpi.hpp>
#include <iostream>
#include "nintlib/nintlib.H"
#include <cmath>
#include <algorithm>
namespace mpi = boost::mpi;

double func(int dim_num, double* a) {
	using namespace std;
//FIXME
	double returnv = 0.0;
	for(int i =0;  i < dim_num; ++i)
		returnv += a[i]*(cos(a[i]) + sin(a[i]));
	return 20000.0*returnv;
//	return ;
}

double access(double* a,int j, int k, int width){
	return a[j + width*k];
}

void change(double* a,int j, int k, int width, double value) {
	a[j + width*k] = value;
}

int main(int argc, char* argv[]) {
	mpi::environment env(argc, argv);
	mpi::communicator world;
	const int TAG_A = 1000;
	const int TAG_B = 2000;

	int it_max = 2;
	int* ind = new int(0);
	int* eval_num = new int(0);
	double tol = 0.000001;

	int dim_num = 5;
	int dim_partition_size = 16;
	int number_of_partitions = 32;

	double* result;
	int* sub_num;
	
	int rank = world.rank();
	int size = world.size() - 1; // Workers

	int num_jobs = (int)std::pow(dim_partition_size, dim_num);
	int num_local_jobs = num_jobs / size;

	if(rank == 0) {
		double** a = new double*[(size +1)];
		double** b = new double*[(size +1)];
		std::cout << "Num_jobs: " << num_jobs << std::endl;
		std::cout << "Num_local_jobs: " << num_local_jobs << " dim_num: " << dim_num << std::endl;
		std::cout << "Array size: " << num_local_jobs*dim_num << std::endl;
		for(int i = 0; i < size + 1; ++i) {
			a[i] = new double[num_local_jobs*dim_num];
			b[i] = new double[num_local_jobs*dim_num];
		}
		int* dims = new int[dim_num];
		for(int i = 0; i < dim_num; i++)
			dims[i] = 0;
		for (int job = 0; job < num_jobs; job++) {
			int r = job % size + 1;
			int j = job / size;
			for (int i = 0; i < dim_num; i++) {
				change(a[r], j, i, dim_num, dims[i] * (1.0/dim_partition_size));
				change(b[r], j, i, dim_num, (dims[i] + 1) * (1.0/dim_partition_size));
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
		int n = num_local_jobs*dim_num;

		for(int i = 1; i < size + 1; ++i) {
			world.isend(i, TAG_A, a[i], n);
			world.isend(i, TAG_B, b[i], n);
		}
		//Receive results
    double result = 0.0;
    double* dummy_result = new double[num_local_jobs];
		for(int i = 0; i < num_local_jobs; ++i)
			dummy_result[i] = 0.0;
    double* local_result = new double[num_local_jobs];
	 	reduce(world, dummy_result, num_local_jobs, local_result,std::plus<double>(),0);
		for(int i = 0; i < num_local_jobs; ++i)
			result += local_result[i];
		std::cout << "local_result: " << result << std::endl;
	}
	else { 

		int n = num_local_jobs*dim_num;
		double* a_local = new double[num_local_jobs*dim_num];
		double* b_local = new double[num_local_jobs*dim_num];
		world.recv(0, TAG_A, a_local, n);
		world.recv(0, TAG_B, b_local, n);

		if(rank == 1) {
			for(int i = 0; i < num_local_jobs + 1; ++i) {		
				for(int j = 0; j < dim_num; ++j) {

			}
			}
		}


		sub_num = new int[dim_num];
		for (int i = 0; i < dim_num; i++)                
			sub_num[i] = number_of_partitions/dim_partition_size;                

		result = new double[num_local_jobs];
		double* a;
		double* b;

//		eval_num_total = 0;
		for (int j = 0; j < num_local_jobs; j++) { 
			a = new double[dim_num];
			b = new double[dim_num];

			for (int i = 0; i < dim_num; i++) {
				a[i] = access(a_local, j, i , dim_num);
				b[i] = access(b_local, j, i , dim_num);
			}                                        
			result[j] = romberg_nd(func, a, b, dim_num, sub_num, it_max, tol, ind, eval_num);

		}

		mpi::reduce(world, result, num_local_jobs, std::plus<double>(), 0);
		
    }

}
