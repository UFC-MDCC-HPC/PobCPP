#include "job.h"
#include "result.h"

class Farm {

   public: 
     void synchronize_jobs();
     void synchronize_results();

   unit Manager 
   {   
      private: 
        list<Job> all_jobs;
        list<Result> all_results;
  
      public: 
        void addJob(Job job);
        Result getNextResult();              
        list<Result> getAllResults();              
        virtual void* packJob(Job job);
        virtual Result unpackResult(void* result);
   };
    
   unit Worker [i:n] 
   {                    
      private: 
        list<Job> local_jobs;
        list<Result> local_results;
     
      public: 
        void perform_jobs();
        virtual Result work(Job job);              
        virtual Job unpackJob(void* job);
        virtual void* packResult(Result result);
    };
 };


