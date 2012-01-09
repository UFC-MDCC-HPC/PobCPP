#ifndef __PVEC__
#define __PVEC__

#include "workarounds.h"
#include "petscvec.h" // FIXME
class ParallelVec {
public:
	parallel unit PVec {
		public:
		PVec(unsigned int i, unsigned int n);
		~PVec();
		
		PetscErrorCode AssemblyBegin();
		PetscErrorCode AssemblyEnd();
		PetscErrorCode Copy(Vec y);
		PetscErrorCode Create(); 
		PetscErrorCode CreateSeq(PetscInt);
		PetscErrorCode Destroy();
		PetscErrorCode Duplicate(PVec *newv);
		PetscErrorCode Exp();
		PetscErrorCode GetArray(PetscScalar *a[]);
		PetscErrorCode GetLocalSize(PetscInt *size);
		PetscErrorCode GetSize(PetscInt* size);
		PetscErrorCode GetValues(PetscInt ni,const PetscInt ix[],PetscScalar y[]);
		PetscErrorCode Set(PetscScalar alpha);
		PetscErrorCode SetFromOptions();
		PetscErrorCode SetSizes(PetscInt n, PetscInt N);
		PetscErrorCode SetValue(int row, PetscScalar value, InsertMode mode);
		PetscErrorCode SetValueLocal(int row, PetscScalar value, InsertMode mode);
		PetscErrorCode SetValues(PetscInt ni, const PetscInt ix[], const PetscScalar y[], InsertMode iora);
		PetscErrorCode View(PetscViewer viewer);

		public: // Should be private
		Vec vec; // Petsc Vec
		MPI_Comm petscomm;
		private:
		int i,n;
	};
};

#endif
