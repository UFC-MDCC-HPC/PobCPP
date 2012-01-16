#include "ksp.pob.h"

ParallelKSP::PKSP::PKSP(unsigned int i, unsigned int n) : i(i), n(n) {
}

ParallelKSP::PKSP::~PKSP() { }

PetscErrorCode ParallelKSP::PKSP::Create() [Communicator comm] {
	PetscCommDuplicate(comm.get_mpi_comm(), &petscomm, PETSC_NULL);
	//return KSPCreate(comm.get_mpi_comm(), &ksp);
	return KSPCreate(petscomm, &ksp);
}

PetscErrorCode ParallelKSP::PKSP::Solve(ParallelVec::PVec& b, ParallelVec::PVec& x) {
	return KSPSolve(ksp, b.vec, x.vec);
}
PetscErrorCode ParallelKSP::PKSP::SetOperators(ParallelMat::PMat& Amat,ParallelMat::PMat& Pmat,MatStructure flag) {
	return KSPSetOperators(ksp, Amat.mat, Pmat.mat, flag);
}
