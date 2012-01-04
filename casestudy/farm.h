#ifndef __FARM_H_
#define __FARM_H_
template<typename Job, typename Result> 
class Farm {
	public: 
	unit Manager {   
		public: 
		Job** all_jobs1;
		Job** all_jobs2;
		Result* all_results;
		unsigned int workers;

		void addJobs(Job** jobs);
		Result getNextResult();              
		Result* getAllResults();              
//		virtual void* packJob(Job* jobs);
//		virtual Result unpackResult(void* result);
		Communicator comm;
	};
	parallel unit Worker {                    
		public: 
		Job* local_jobs1;
		Job* local_jobs2;
		Result* local_results;

		void perform_jobs();
//		virtual Result work(Job job);              
//		virtual Job unpackJob(void* job);
//		virtual void* packResult(Result result);
		//protected:
		int i,j;
		Communicator comm;
	};
};



#endif
