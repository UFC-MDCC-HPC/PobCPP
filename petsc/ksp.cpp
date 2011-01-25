#include "ksp.h.pob"

ParallelKSP::PKSP::PKSP(unsigned int i, unsigned int n) : i(i), n(n) {
	create_unit<ParallelKSP>(this, i, n);
}

ParallelKSP::PKSP::~PKSP() { }

PetscErrorCode ParallelKSP::PKSP::Create() {
		return KSPCreate(petscomm, &ksp);
}

PetscErrorCode ParallelKSP::PKSP::Solve(ParallelVec::PVec& b, ParallelVec::PVec& x) {
	return KSPSolve(ksp, b.vec, x.vec);
}
PetscErrorCode ParallelKSP::PKSP::SetOperators(ParallelMat::PMat& Amat,ParallelMat::PMat& Pmat,MatStructure flag) {
	return KSPSetOperators(ksp, Amat.mat, Pmat.mat, flag);
}
