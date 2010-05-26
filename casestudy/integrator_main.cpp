#include "integrator_main.h"

#include "integrator.h"

int IntegratorMain::Root::main() {
      #pragma omp parallel
      {
        Romberg_Integrator::Manager *m 
             = new Romberg_Integrator::Manager(0.0, 1.0, 5, 2);
				create_unit<Romberg_Integrator>(m);
        double result;
        #pragma omp sections
        {
            #pragma omp section
             m->generate_subproblems();         
            #pragma omp section
             m->synchronize_jobs();   
            #pragma omp section
             m->work(); 
            #pragma omp section
             m->synchronize_results();   
            #pragma omp section
            result = m->combine_subproblems_results();      

        }      
        cout << "Result is " << result << endl;
      }
    }
}

int IntegratorMain::Peer::main() {
      #pragma omp parallel 
      {
        RombergIntegrator::Worker *w = new RombergIntegrator::Worker(function, 0.00001, 16);
				create_unit<Romberg_Integrator>(w, j, n);
        #pragma omp sections
        {
            #pragma omp section
             w-> distribute_subproblems();         
            #pragma omp section
             w -> integrate();
        }
      }

}

