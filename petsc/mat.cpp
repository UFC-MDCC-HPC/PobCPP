#include "mat.pob.h"
#include "petscsys.h"

ParallelMat::PMat::PMat(unsigned int i, unsigned int n) : i(i), n(n) {
}

ParallelMat::PMat::~PMat() {	
}

PetscErrorCode ParallelMat::PMat::AssemblyBegin(MatAssemblyType type) {
	return MatAssemblyBegin(mat, type);
}

PetscErrorCode ParallelMat::PMat::AssemblyEnd(MatAssemblyType type) {
	return MatAssemblyEnd(mat, type);
}
PetscErrorCode ParallelMat::PMat::Create() [Communicator comm] {
	PetscCommDuplicate(comm.get_mpi_comm(), &petscomm, PETSC_NULL);
	return MatCreate(petscomm, &mat); //FIXME	
}

PetscErrorCode ParallelMat::PMat::GetSize(PetscInt *sizem, PetscInt *sizen) {
	return MatGetSize(mat, sizem, sizen);
}
	
PetscErrorCode ParallelMat::PMat::Mult(ParallelVec::PVec& x, ParallelVec::PVec& y) {
	return MatMult(mat, x.vec, y.vec);
}

PetscErrorCode ParallelMat::PMat::SetFromOptions() {
	return MatSetFromOptions(mat);
}

PetscErrorCode ParallelMat::PMat::SetValues(PetscInt m,const PetscInt idxm[],PetscInt n,const PetscInt idxn[],const PetscScalar v[],InsertMode addv) {
	return MatSetValues(mat, m, idxm, n, idxn, v, addv);
}
PetscErrorCode ParallelMat::PMat::SetSizes(PetscInt m, PetscInt n, PetscInt M, PetscInt N) {
	return MatSetSizes(mat, m, n, M, N);
}
	
