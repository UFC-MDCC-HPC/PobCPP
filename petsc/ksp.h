#ifndef __PKSP__
#define __PKSP__
#include "vec.h.pob"
#include "mat.h.pob"
#include "workarounds.h"
#include "petscksp.h" // FIXME
class ParallelKSP {
public:
	unit PKSP [i:n] {
		public:
		PKSP(unsigned int i, unsigned int n);
		~PKSP();
		
		PetscErrorCode Create();
		PetscErrorCode Solve(ParallelVec::PVec& b, ParallelVec::PVec& x);
		PetscErrorCode SetOperators(ParallelMat::PMat& Amat,ParallelMat::PMat& Pmat,MatStructure flag);
		public: // Should be private
		KSP ksp;
		MPI_Comm petscomm;
	};

};


#endif
