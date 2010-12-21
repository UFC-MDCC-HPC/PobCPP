#ifndef __BUCKETSORT_H_
#define __BUCKETSORT_H_
#include "pob_sort.h"
class BucketSort : public Sorter {
public:
	void parallel sort();

	unit Worker [i:n] : public Sorter::Worker {
		public:
      Worker(int i, int n);
			void /*parallel*/ sort();
		private:
			void make_numbers(long int big_array[], int n, int n_bar, int p);
			void sequential_sort(long int array[], int size);
			int minpos(long int array[], int eff_size);
	}

};

#endif
