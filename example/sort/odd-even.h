#ifndef __ODDEVENSORT_H_
#define __ODDEVENSORT_H_
#include "pob_sort.h"
class OddEven : public Sorter {
public:
	void parallel sort();

	unit Worker [i:n] : public Sorter::Worker {
		public:
      Worker(int i, int n);
			void /*parallel*/ sort();
		private:
			int IncOrder(const void *e1, const void *e2);
			void CompareSplit(int nlocal, int *elmnts, int *relmnts, int *wspace,int keepsmall);
	}

};

#endif
