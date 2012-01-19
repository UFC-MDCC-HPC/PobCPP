#include "integrator_main.pob.h"

#include "integrator.pob.h"
#include <iostream>
#include <cmath>
#include <algorithm>

int IntegratorMain::Root::main(int dim_num, int dim_partition_size, int number_of_partitions, int workers) {
	Communicator world;
	int rank = world.rank();
	int num_jobs = (int)std::pow(dim_partition_size, dim_num);
	int num_local_jobs = num_jobs / workers;
//	m->dim_num = dim_num;
//	m->dim_partition_size = dim_partition_size;
//	m->workers = workers;
	//m->num_jobs = num_jobs;
//	m->num_local_jobs = num_local_jobs;
//	m->number_of_partitions = number_of_partitions;
	Romberg_Integrator::Manager *m  = new Romberg_Integrator::Manager(dim_num, dim_partition_size, number_of_partitions, num_jobs, num_local_jobs, workers);
	std::cout << "(" << rank << ")" << "Trying to create Manager. " << std::endl;
//	create_unit<Romberg_Integrator>(m);
	std::cout << "(" << rank << ")" << "Manager created. " << std::endl;
	double result = 0.0f;
	std::cout << "(" << rank << ")" << "Jobs created: " << num_jobs << std::endl;
	m->generate_subproblems();         
	std::cout << "(" << rank << ")" << "Root - Problems generated " << std::endl;
	m->synchronize_jobs();   
	std::cout << "(" << rank << ")" << "Root - Jobs synchronized " << std::endl;
	m->synchronize_results();   
	std::cout << "(" << rank << ")" << "Root - Results synchronized " << std::endl;
	result = m->combine_subproblems_results();      
	std::cout << "(" << rank << ")" << "Root - Result is " << result << std::endl;
	return 0;
}

int IntegratorMain::Peer::main(int it_max, double tol, int dim_num, int dim_partition_size, int number_of_partitions) {
	int workers = n;
	int num_jobs = (int)std::pow(dim_partition_size, dim_num);
	int num_local_jobs = num_jobs / workers;
/*	w->tol = tol;
	w->number_of_partitions = number_of_partitions;
	w->dim_num = dim_num;
	w->dim_partition_size = dim_partition_size;
	w->num_local_jobs = num_local_jobs;*/
	Romberg_Integrator::Worker *w = new Romberg_Integrator::Worker(tol, dim_num,dim_partition_size, number_of_partitions, num_local_jobs, j,n);
	//create_unit<Romberg_Integrator>(w,std::make_pair(j, workers));
	std::cout << "Worker " << j+1 << "," << workers << " created." << std::endl;
	w->synchronize_jobs();   
	std::cout << "W(" << j+1 << "," << n << ") " << "Jobs synchronized " << std::endl;
	w->work();
	std::cout << "W(" << j+1 << "," << n << ") "<< "Work done " << std::endl;
	w->synchronize_results();   
	std::cout << "W(" << j+1 << "," << n << ") "<< "Results synchronized " << std::endl;
	return 0;
}

