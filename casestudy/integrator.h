#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__
#include "farm.h.pob"

double func(int dim_num, double* a);
class Romberg_Integrator: public Farm<double, double> {
	public:
	unit Manager : public Farm<double, double>::Manager {   
		public: 
		Manager(int dim_num, int dim_partition_size, int number_of_partitions, int num_jobs, int num_local_jobs, int workers);
		int inf, sup, dim_num, dim_partition_size;
		int number_of_partitions;
		int num_jobs;
		int num_local_jobs;
		int workers;

		void generate_subproblems();
		double combine_subproblems_results();
		void synchronize_jobs();
		void synchronize_results();
	};

	parallel unit Worker : virtual public Farm<double, double>::Worker	{
		public: 
		Worker(double tol, int dim_num, int dim_partition_size, int number_of_partitions, int num_local_jobs, int i, int j);
		int inf, sup, dim_num, dim_partition_size;
		int number_of_partitions;
		int next_unsolved_subproblem; 
		int num_local_jobs;
		double tol;
		void integrate();
		void work(); 
		void synchronize_jobs(); 
		void synchronize_results();
	};
};

#endif
