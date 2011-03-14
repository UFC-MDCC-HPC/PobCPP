#ifndef __BUCKETSORT_H_
#define __BUCKETSORT_H_
#include "sort.h.pob"
class BucketSort : public Sorter {
public:
	void /*parallel*/ sort();

	unit Worker [i:n] : public Sorter::Worker {
		public:
      Worker(int i, int n);
			void /*parallel*/ sort();
		private:
			void sequential_sort(long int array[], int size);
			int minpos(long int array[], int eff_size);
	};

};

#endif
