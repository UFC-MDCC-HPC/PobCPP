#ifndef __FARM_H__
#define __FARM_H__
#include "unit_type.h"
#include "unit.h"

template <class Job, class Result >
class Farm {
  public:
/*unit_decl*/ class Manager : public Pobcpp::Unit {
	public:
		Job **all_jobs1;
    Job **all_jobs2;
    Result *all_results;
    unsigned int workers;
    void addJobs(Job **jobs);
    Result getNextResult();
    Result *getAllResults();
//    virtual void *packJob(Job *jobs);
 //   virtual Result unpackResult(void *result);
  };
  /*unit_decl*/ class Worker : public Pobcpp::Unit {
		public:
    Job *local_jobs1;
    Job *local_jobs2;
    Result *local_results;
void perform_jobs();
  //  virtual Result work(Job job);
  //  virtual Job unpackJob(void *job);
  //  virtual void *packResult(Result result);
  };
  /*static class Pobcpp::Pob_Type_Array  __get_types() {
    class Pobcpp::Pob_Type_Array  pobtypes ( (2)); 
    ( ( (pobtypes).add_type) ( (0)));
 ( ( (pobtypes).add_type) ( (1),  (1)));
return (pobtypes);
}*/
};

#endif
