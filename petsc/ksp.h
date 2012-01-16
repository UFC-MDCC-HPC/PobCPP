#ifndef __PKSP__
#define __PKSP__
#include "vec.pob.h"
#include "mat.pob.h"
#include "workarounds.h"
#include "petscksp.h" // FIXME
class ParallelKSP {
public:
	parallel unit PKSP {
		public:
		PKSP(unsigned int i, unsigned int n);
		~PKSP();
		
		PetscErrorCode Create() [Communicator comm];
		PetscErrorCode Solve(ParallelVec::PVec& b, ParallelVec::PVec& x);
		PetscErrorCode SetOperators(ParallelMat::PMat& Amat,ParallelMat::PMat& Pmat,MatStructure flag);
		public: // Should be private
		KSP ksp;
		MPI_Comm petscomm;
		private:
		int i,n;
	};

};


#endif
