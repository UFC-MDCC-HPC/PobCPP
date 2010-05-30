#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__

#include "farm.h"
#include "unit_type.h"
#include "unit.h"

double func(int dim_num, double *a);
class Romberg_Integrator : public Farm<double, double> {
  public:
/*unit_decl*/ class Manager : public Farm<double, double>::Manager {
    public:
		Manager(int dim_num, 
		        int dim_partition_size, int number_of_partitions, int num_jobs, int num_local_jobs, int workers) : 
		        dim_num(dim_num), dim_partition_size(dim_partition_size), number_of_partitions(number_of_partitions), num_jobs(num_jobs), num_local_jobs(num_local_jobs), workers(workers) { }
    int dim_num;
    int dim_partition_size;
    int number_of_partitions;
    int num_jobs;
    int num_local_jobs;
		int workers;
    void generate_subproblems();
    double combine_subproblems_results();
    void synchronize_jobs();
    void synchronize_results();
  };
  /*unit_decl*/ class Worker : public Farm<double, double>::Worker {
    public:
		Worker(int it_max, double tol, int dim_num, int dim_partition_size, int number_of_partitions, int num_local_jobs, int i, int n) : it_max(it_max), tol(tol), dim_num(dim_num), dim_partition_size(dim_partition_size), number_of_partitions(number_of_partitions), num_local_jobs(num_local_jobs), i(i), n(n){
		}
		int it_max;
		double tol;
    int dim_num;
    int dim_partition_size;
		int number_of_partitions;
    int num_local_jobs;
    unsigned int const i;
    unsigned int const n;
    void work();
    void synchronize_jobs();
    void synchronize_results();
	};
  static class Pobcpp::Pob_Type_Array  __get_types() {
    class Pobcpp::Pob_Type_Array  pobtypes ( (2)); 
    ( ( (pobtypes).add_type</*unit*/ class Romberg_Integrator::Manager > ) ( (0)));
 ( ( (pobtypes).add_type</*unit*/ class Romberg_Integrator::Worker > ) ( (1),  (1)));
return (pobtypes);
	}
};
#endif
