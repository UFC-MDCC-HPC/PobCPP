#include "integrator.pob.h"
#include "nintlib/nintlib.H"
#include <cmath>
#include <iostream>

double func(int dim_num, double* a) {
	using namespace std;
//FIXME
	double returnv = 0.0;
	for(int i =0;  i < dim_num; ++i)
		returnv += a[i]*(cos(a[i]) + sin(a[i]));
	return 20000.0*returnv;
//	return ;
}

double access(double* a,int j, int k, int width) {
		return a[j*width + k];
}

void change(double* a,int j, int k, int width, double value) {
		a[j*width + k] = value;
}
//Romberg_Integrator::Worker::Worker(int i, int n) : i(i), n(n) { }

Romberg_Integrator::Manager::Manager(int dim_num, int dim_partition_size, int number_of_partitions, int num_jobs, int num_local_jobs, int workers) :
	dim_num(dim_num), dim_partition_size(dim_partition_size), number_of_partitions(number_of_partitions), num_jobs(num_jobs), num_local_jobs(num_local_jobs), workers(workers) { }

Romberg_Integrator::Worker::Worker(double tol, int dim_num, int dim_partition_size, int number_of_partitions, int num_local_jobs, int _i, int _j) : dim_num(dim_num), dim_partition_size(dim_partition_size), number_of_partitions(number_of_partitions), num_local_jobs(num_local_jobs)//, i(i), j(j) { }
																																	  { i = _i; j = _j; }

void Romberg_Integrator::Manager::generate_subproblems() {
	int size = workers;
	all_jobs1 = new double*[(workers)];
	all_jobs2 = new double*[(workers)];
	for(int i = 0; i < size; ++i) {
		all_jobs1[i] = new double[num_local_jobs*dim_num];
		all_jobs2[i] = new double[num_local_jobs*dim_num];
	}
	int* dims = new int[dim_num];
	for(int i = 0; i < dim_num; i++)
		dims[i] = 0;
	for (int job = 0; job < num_jobs; job++) {
//		int r = job % size + 1;
		int r = job % size;
		int j = job / size;
		for (int i = 0; i < dim_num; i++) {
			change(all_jobs1[r], j, i, dim_num, dims[i] * (1.0/dim_partition_size));
			change(all_jobs2[r], j, i, dim_num, (dims[i] + 1) * (1.0/dim_partition_size));
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
}
double Romberg_Integrator::Manager::combine_subproblems_results() {
	double result = 0.0;
	for(int i = 0; i < num_local_jobs; ++i)
		result += all_results[i];
	return result;
}

void Romberg_Integrator::Manager::synchronize_jobs(){
	unsigned int n = num_local_jobs*dim_num;
	for(unsigned int i = 0; i < workers; i++) {
		comm.isend(i+1, 100, all_jobs1[i], n);
		comm.isend(i+1, 100, all_jobs2[i], n);
	}
}
void Romberg_Integrator::Manager::synchronize_results() {
	double* dummy_result = new double[num_local_jobs];
	for(int i = 0; i < num_local_jobs; ++i)
		dummy_result[i] = 0.0;
//	double* local_result = new double[num_local_jobs];
	all_results = new double[num_local_jobs];
	comm.reduce(dummy_result, num_local_jobs, all_results, MPI_SUM, 0);
}

void Romberg_Integrator::Worker::synchronize_jobs() {
	unsigned int n = num_local_jobs*dim_num;
	local_jobs1 = new double[n]; 
	local_jobs2 = new double[n]; 
	comm.recv(0, 100, local_jobs1, n);
	comm.recv(0, 100, local_jobs2, n);
}

void Romberg_Integrator::Worker::synchronize_results() {
	comm.reduce(local_results, num_local_jobs, MPI_SUM, 0);
}

void Romberg_Integrator::Worker::work() {
	int* sub_num = new int[dim_num];
	int* eval_num = new int(0);
	int* ind = new int(0);
	for (int i = 0; i < dim_num; i++)                
		sub_num[i] = number_of_partitions/dim_partition_size;                

	local_results = new double[num_local_jobs];
	double* a;
	double* b;
//		eval_num_total = 0;
	for (int j = 0; j < num_local_jobs; j++) { 
		a = new double[dim_num];
		b = new double[dim_num];

		for (int i = 0; i < dim_num; i++) {
			a[i] = access(local_jobs1, j, i , dim_num);
			b[i] = access(local_jobs2, j, i , dim_num);
		}
		int it_max = 9999;
		local_results[j] = romberg_nd(func, a, b, dim_num, sub_num, it_max, tol, ind, eval_num);
	}
}

