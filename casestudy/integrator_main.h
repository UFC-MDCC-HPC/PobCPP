#ifndef __INTEGRATOR_MAIN_H__
#define __INTEGRATOR_MAIN_H__

class IntegratorMain {

  unit Root {
		public:
		int main(int dim_num, int dim_partition_size, int number_of_partitions, int workers);
  };

  parallel unit Peer {
		public:
		Peer(int j, int n) : j(j), n(n) { }
		int main(int it_max, double tol, int dim_num, int dim_partition_size, int number_of_partitions);
		int j,n;
  };
};
#endif
