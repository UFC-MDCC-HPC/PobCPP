#include "farm.h"
#include "unit_type.h"
#include "unit.h"

class Romberg_Integrator: public Farm {

   unit Manager : public Farm::Manager
   {   
      private: 
        int inf, sup, dim_num, partition_size;
    
      public: 
        Manager(int inf, int sup, int dim_num, int psize) : 
            inf(inf), sup(sup), dim_num(dim_num), 
            partition_size(psize) { }
              
      public: 
        void generate_subproblems();
        double combine_subproblems_results();
        void* packJob(list<Job> jobs);
        list<Result> unpackResult(void* result);
   };
    
   unit Worker [i:n] : public Farm::Worker
   {
      private:
        int number_of_partitions;
        int next_unsolved_subproblem; 
        double (*function)(double*);
        
      public: 
        Worker(double (*f)(double*), int tol, int nop) : 
             function(f), number_of_partitions(nop), 
             next_unsolved_subproblem(0), tolerance(tol) { }
        
      public: 
        double Result work(Job job);              
        list<Job> unpackJob(void* jobs);
        void* packResult(list<Result> result);    
   };
 };
