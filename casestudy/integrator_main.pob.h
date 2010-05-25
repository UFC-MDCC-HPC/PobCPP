class IntegratorMain {

  public: int main();

  unit Root 
  {
    int main() 
    {
      #pragma omp parallel
      {
        Romberg_Integrator::Manager *m 
             = new Romberg_Integrator::Manager
                          (0.0, 1.0, 5, 2);
//        m->channel_initialize();
        double result;
        #pragma omp sections
        {
            #pragma omp section
             m -> generate_subproblems();         
            #pragma omp section
             m -> synchronize_jobs();   
            #pragma omp section
             m -> work(); 
            #pragma omp section
             m -> synchronize_results();   
            #pragma omp section
            result = m->combine_subproblems_results();      

        }      
        cout << "Result is " << result << endl;
      }
    }
  };

  unit Peer[j:n] 
  {
    int main() 
    {
      #pragma omp parallel 
      {
        RombergIntegrator::Worker *w 
             = new RombergIntegrator::Worker
                          (function, 1D-5, 16);
//        w->channel_initialize(j);   
        #pragma omp sections
        {
            #pragma omp section
             w-> distribute_subproblems();         
            #pragma omp section
             w -> integrate();
        }
      }
    }  
  };
};
