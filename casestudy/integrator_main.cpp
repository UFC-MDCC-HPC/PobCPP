#include "integrator_main.h.pob"

#include "integrator.h.pob"
#include <iostream>
#include <cmath>
#include <algorithm>

int IntegratorMain::Root::main(int dim_num, int dim_partition_size, int number_of_partitions, int workers) {
	int num_jobs = (int)std::pow(dim_partition_size, dim_num);
	int num_local_jobs = num_jobs / workers;
//	m->dim_num = dim_num;
//	m->dim_partition_size = dim_partition_size;
//	m->workers = workers;
	//m->num_jobs = num_jobs;
//	m->num_local_jobs = num_local_jobs;
//	m->number_of_partitions = number_of_partitions;
	Romberg_Integrator::Manager *m  = new Romberg_Integrator::Manager(dim_num, dim_partition_size, number_of_partitions, num_jobs, num_local_jobs, workers);
	std::cout << "Trying to create Manager. " << std::endl;
//	create_unit<Romberg_Integrator>(m);
	std::cout << "Manager created. " << std::endl;
	double result;
	std::cout << "Jobs created: " << num_jobs << std::endl;
	m->generate_subproblems();         
	std::cout << "Root - Problems generated " << std::endl;
	m->synchronize_jobs();   
	std::cout << "Root - Jobs synchronized " << std::endl;
	m->synchronize_results();   
	std::cout << "Root - Results synchronized " << std::endl;
	result = m->combine_subproblems_results();      
	std::cout << "Root - Result is " << result << std::endl;
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
	std::cout << "Worker " << j << "," << workers << " created." << std::endl;
	w->synchronize_jobs();   
	std::cout << "W(" << j << "," << n << ") " << "Jobs synchronized " << std::endl;
	w->work();
	std::cout << "W(" << j << "," << n << ") "<< "Work done " << std::endl;
	w->synchronize_results();   
	std::cout << "W(" << j << "," << n << ") "<< "Results synchronized " << std::endl;
	return 0;
}

