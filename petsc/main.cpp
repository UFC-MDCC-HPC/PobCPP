
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
#include "ksp.h.pob"
#include "vec.h.pob"
#include "mat.h.pob"
#include <iostream>
#include "communication.h"
extern int PetscSetCommWorld(MPI_Comm comm);
#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc,char **argv)
{
	pob_init(argc, argv);
  PetscInitialize(&argc,&argv,(char *)0,help);
  PetscErrorCode ierr;
  PetscInt       N = 0;
  PetscReal      norm;
	int rank = -1;
	int size = 0;

	std::cout << "PetscInitialize" << std::endl;
	MPI_Comm_size(PETSC_COMM_WORLD, &size);
	MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
	std::cout << "PVec sera construido - (" << rank << "," << size << ")" << std::endl;
	ParallelKSP::PKSP            ksp(rank, size);
	ParallelMat::PMat            C(rank,size); 
	ParallelVec::PVec            u(rank,size);
	ParallelVec::PVec            b(rank,size);
	ParallelVec::PVec            x(rank,size);

  /* create stiffness matrix */
  ierr = C.Create();CHKERRQ(ierr);
  ierr = C.SetSizes(PETSC_DECIDE,PETSC_DECIDE,N,N);CHKERRQ(ierr);
  ierr = C.SetFromOptions();CHKERRQ(ierr);
  ierr = C.AssemblyBegin(MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  ierr = C.AssemblyEnd(MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  
	std::cout << "Finalize" << std::endl;
  ierr = PetscFinalize();CHKERRQ(ierr);
	MPI_Finalize();	
  return 0;


  /* create right hand side and solution 

  ierr = VecCreateSeq(PETSC_COMM_SELF,N,&u);CHKERRQ(ierr); 
  ierr = VecDuplicate(u,&b);CHKERRQ(ierr);
  ierr = VecDuplicate(u,&x);CHKERRQ(ierr);
  ierr = VecSet(u,0.0);CHKERRQ(ierr);
  ierr = VecSet(b,0.0);CHKERRQ(ierr);

  ierr = VecAssemblyBegin(b);CHKERRQ(ierr);
  ierr = VecAssemblyEnd(b);CHKERRQ(ierr);

  ierr = KSPCreate(PETSC_COMM_WORLD,&ksp);CHKERRQ(ierr);
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
}
 
