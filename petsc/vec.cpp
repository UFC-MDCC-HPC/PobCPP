#include "vec.h.pob"
#include "petscsys.h"

ParallelVec::PVec::PVec(unsigned int i, unsigned int n) : i(i), n(n) { }

ParallelVec::PVec::~PVec() { }

PetscErrorCode ParallelVec::PVec::AssemblyBegin() {
	return VecAssemblyBegin(vec);
}

PetscErrorCode ParallelVec::PVec::AssemblyEnd() {
	return VecAssemblyEnd(vec);
}

PetscErrorCode ParallelVec::PVec::Exp() {
	return VecExp(vec);
}
PetscErrorCode ParallelVec::PVec::Copy(Vec y) {
	return VecCopy(vec, y); //FIXME
}

PetscErrorCode ParallelVec::PVec::Create() [Communicator comm] {
	petscomm = comm->get_mpi_comm();
	int data = 1000;
	std::cout << "Testing Broadcast before: " << data << std::endl;
	if(i == 0)
		data = 250;

//	comm->broadcast<PVec>(0, data);
	std::cout << "Broadcast: " << data << std::endl;

//	return VecCreate(comm->get_mpi_comm(), &vec);
	PetscCommDuplicate(comm->get_mpi_comm(), &petscomm, PETSC_NULL);
	return VecCreate(petscomm, &vec); //FIXME	
}

PetscErrorCode ParallelVec::PVec::CreateSeq(PetscInt n) [Communicator comm] {
	petscomm = comm->get_mpi_comm();
	int data = 1000;
	std::cout << "Testing Broadcast before: " << data << std::endl;
	if(i == 0)
		data = 250;

	comm->broadcast<PVec>(0, data);
	std::cout << "Broadcast: " << data << std::endl;

//	return VecCreate(comm->get_mpi_comm(), &vec);
	PetscCommDuplicate(comm->get_mpi_comm(), &petscomm, PETSC_NULL);
	return VecCreateSeq(petscomm, n, &vec); //FIXME	
}

PetscErrorCode ParallelVec::PVec::Destroy() {
	return VecDestroy(vec); //FIXME	
}

PetscErrorCode ParallelVec::PVec::Duplicate(PVec* newv) {
	return VecDuplicate(vec, &newv->vec);
}

PetscErrorCode ParallelVec::PVec::GetArray(PetscScalar *a[]) {
	return VecGetArray(vec, a);
}

PetscErrorCode ParallelVec::PVec::GetLocalSize(PetscInt *size) {
	return VecGetLocalSize(vec, size);
}

PetscErrorCode ParallelVec::PVec::GetSize(PetscInt *size) {
	return VecGetSize(vec, size);
}

PetscErrorCode ParallelVec::PVec::GetValues(PetscInt ni,const PetscInt ix[],PetscScalar y[]) {
	return VecGetValues(vec, ni, ix, y);
}

PetscErrorCode ParallelVec::PVec::Set(PetscScalar alpha) {
	return VecSet(vec, alpha);
}

PetscErrorCode ParallelVec::PVec::SetFromOptions() {
	return VecSetFromOptions(vec);
}

PetscErrorCode ParallelVec::PVec::SetSizes(PetscInt n, PetscInt N) {
	return VecSetSizes(vec, n, N);
}

PetscErrorCode ParallelVec::PVec::SetValue(int row, PetscScalar value, InsertMode mode) {
	return VecSetValue(vec, row, value, mode);
}

PetscErrorCode ParallelVec::PVec::SetValueLocal(int row, PetscScalar value, InsertMode mode) {
	return VecSetValueLocal(vec, row, value, mode);
}

PetscErrorCode ParallelVec::PVec::SetValues(PetscInt ni, const PetscInt ix[], const PetscScalar y[], InsertMode iora) {
	return VecSetValues(vec, ni, ix, y, iora);
}

PetscErrorCode ParallelVec::PVec::View(PetscViewer viewer) {
	return VecView(vec, viewer);
}
