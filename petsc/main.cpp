
static char help[] = "Builds a parallel vector with 1 component on the firstprocessor, 2 on the second, etc.\n\
  Then each processor adds one to all elements except the last rank.\n\n";

/*T
   Concepts: vectors^assembling vectors;
   Processors: n
T*/

/* 
  Include "petscvec.h" so that we can use vectors.  Note that this file
  automatically includes:
     petscsys.h       - base PETSc routines   petscis.h     - index sets
     petscviewer.h - viewers
*/
//#include "petscvec.h"
#include "ksp.pob.h"
#include "vec.pob.h"
#include "mat.pob.h"
#include <iostream>
extern int PetscSetCommWorld(MPI_Comm comm);
#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc,char **argv)
{
	MPI_Init(&argc, &argv);
  PetscInitialize(&argc,&argv,(char *)0,help);
  PetscErrorCode ierr;
  PetscInt       N = 0;
	PetscInt       M = 2;
  PetscReal      norm;
	int rank = -1;
	int size = 0;

	std::cout << "PetscInitialize" << std::endl;
	Communicator comm;
	size = comm.size();
	rank = comm.rank();
	std::cout << "PVec sera construido - (" << rank << "," << size << ")" << std::endl;
	ParallelKSP::PKSP            ksp;
	ParallelMat::PMat            C;
	ParallelVec::PVec            u;
	ParallelVec::PVec            b;
	ParallelVec::PVec            x;

  /* create stiffness matrix */
  ierr = C.Create(comm);CHKERRQ(ierr);
  ierr = C.SetSizes(PETSC_DECIDE,PETSC_DECIDE,N,N);CHKERRQ(ierr);
  ierr = C.SetFromOptions();CHKERRQ(ierr);
  ierr = C.AssemblyBegin(MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  ierr = C.AssemblyEnd(MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);

 // ierr = u.CreateSeq(N, comm);CHKERRQ(ierr); 
  ierr = u.Create(comm);CHKERRQ(ierr); 
	ierr = u.SetSizes(PETSC_DECIDE, M);CHKERRQ(ierr);
	ierr = u.SetFromOptions();
  ierr = u.Set(0.0);CHKERRQ(ierr);
  ierr = u.Duplicate(&b);CHKERRQ(ierr);
  ierr = u.Duplicate(&x);CHKERRQ(ierr);

ierr = b.Set(0.0);CHKERRQ(ierr);
  ierr = b.AssemblyBegin();CHKERRQ(ierr);
  ierr = b.AssemblyEnd();CHKERRQ(ierr);
  
	ierr = ksp.Create(comm);CHKERRQ(ierr);


/*  ierr = KSPCreate(PETSC_COMM_WORLD,&ksp);CHKERRQ(ierr);
  ierr = KSPSetOperators(ksp,C,C,DIFFERENT_NONZERO_PATTERN);CHKERRQ(ierr);
  ierr = KSPSetFromOptions(ksp);CHKERRQ(ierr);
  ierr = KSPSolve(ksp,b,u);CHKERRQ(ierr);

  ierr = MatMult(C,u,x);CHKERRQ(ierr);
  ierr = VecAXPY(x,-1.0,b);CHKERRQ(ierr);
  ierr = VecNorm(x,NORM_2,&norm);CHKERRQ(ierr);

  ierr = KSPDestroy(ksp);CHKERRQ(ierr);
  ierr = VecDestroy(u);CHKERRQ(ierr);
  ierr = VecDestroy(x);CHKERRQ(ierr);
  ierr = VecDestroy(b);CHKERRQ(ierr);
  ierr = MatDestroy(C);CHKERRQ(ierr);*/
	std::cout << "Finalize" << std::endl;
  ierr = PetscFinalize();CHKERRQ(ierr);
	MPI_Finalize();	
  return 0;
}
 
