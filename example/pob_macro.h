#ifndef __POB_MACRO_H__
#define __POB_MACRO_H__
// #include directives
#include "pob.def.h"

parallel_class (POb) { // parallel_class
public:
	POb(void);
	static boost::mpi::communicator world;
	int main(void);
	
	unit_def(A) {
	public:
		unit_cons(A) { }
		void main();
		void compute(void);
	private:
		int a;
	};

	unit_def(B) {
	public:
		unit_cons(B) { }
		void main();
		void compute_other_thing(void);
	private:
		int b;
	};

};

#endif

