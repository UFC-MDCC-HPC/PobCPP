#ifndef __INTEGRATOR_MAIN_H__
#define __INTEGRATOR_MAIN_H__

#include "unit_type.h"
#include "unit.h"

class IntegratorMain {
  public:
int main();
  /*unit_decl*/ class Root : public Pobcpp::Unit {
		public:
    int main( int dim_num, 
		        int dim_partition_size, int number_of_partitions, int workers);
  };
  /*unit_decl*/ class Peer : public Pobcpp::Unit {
		public:
		Peer(int j, int n) : j(j), n(n) { };
    int main(int it_max, double tol, int dim_num, 
		        int dim_partition_size, int number_of_partitions);
    unsigned int const j;
    unsigned int const n;
  };
  static class Pobcpp::Pob_Type_Array  __get_types() {
    class Pobcpp::Pob_Type_Array  pobtypes ( (2)); 
    ( ( (pobtypes).add_type</*unit*/ class IntegratorMain::Root > ) ( (0)));
 ( ( (pobtypes).add_type</*unit*/ class IntegratorMain::Peer > ) ( (1),  (1)));
return (pobtypes);
}
};
#endif
