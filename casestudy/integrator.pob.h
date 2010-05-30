#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__
#include "farm.h"
#include "unit_type.h"
#include "unit.h"

double func(int dim_num, double* a);
class Romberg_Integrator: public Farm<double, double> {
	public:
	unit Manager : public Farm<double, double>::Manager {   
		public: 
			Manager(int a) : workers(a) { }
		int workers;
		int inf, sup, dim_num, dim_partition_size;
		int num_local_jobs;
		int num_jobs;
		int number_of_partitions;

		void generate_subproblems();
		double combine_subproblems_results();
		void synchronize_jobs();
		void synchronize_results();
	};

	unit Worker [i:n] : public Farm<double, double>::Worker	{
		public: 
		Worker(int i, int n) : i(i), n(n) { }
		int inf, sup, dim_num, dim_partition_size;
		int number_of_partitions;
		int next_unsolved_subproblem; 
		int inf, sup, dim_num, dim_partition_size;
		int num_local_jobs;
		double tol;
		void integrate();
		void work(); 
		void synchronize_jobs();
		void synchronize_results();
	};
};

#endif
