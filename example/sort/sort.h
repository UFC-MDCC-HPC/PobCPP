#ifndef __SORTER_H__
#define __SORTER_H__

class Sorter {
public:
	void /*parallel*/ sort();
	unit Worker [i:n] {
		public:
			void /*parallel*/virtual sort() = 0;
      void set(int* nums, int size);
		protected:
			Worker(unsigned int i, unsigned int n) : i(i), n(n) { }
			int* nums;
			int size;
	};

};

#endif

