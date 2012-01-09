#ifndef __PMAT__
#define __PMAT__

#include "workarounds.h"
#include "petscmat.h" // FIXME
#include "vec.h.pob"
class ParallelMat {
public:
	parallel unit PMat {
	public:
		PMat(unsigned int i, unsigned int n);
		~PMat();

		PetscErrorCode AssemblyBegin(MatAssemblyType type);
		PetscErrorCode AssemblyEnd(MatAssemblyType type);
		PetscErrorCode Copy(Mat y, MatStructure str);
		PetscErrorCode Create(); 
		PetscErrorCode Destroy();
		PetscErrorCode GetSize(PetscInt* sizem, PetscInt* sizen);
		PetscErrorCode Mult(ParallelVec::PVec& x, ParallelVec::PVec& y);
		PetscErrorCode SetFromOptions();
		PetscErrorCode SetSizes(PetscInt m, PetscInt n, PetscInt M, PetscInt N);
		PetscErrorCode SetValues(PetscInt m,const PetscInt idxm[],PetscInt n,const PetscInt idxn[],const PetscScalar v[],InsertMode addv);

	public:
		Mat mat;
		MPI_Comm petscomm;
	private:
		int i,n;
	};

};

#endif
