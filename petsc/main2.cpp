
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
#include "vec.h.pob"
#include <iostream>
#include "communication.h"
extern int PetscSetCommWorld(MPI_Comm comm);
#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc,char **argv)
{
	pob_init(argc, argv);
  PetscInitialize(&argc,&argv,(char *)0,help);
	int rank = -1;
	int size = 0;
  PetscErrorCode ierr;
  PetscInt       i,N;
  PetscScalar    one = 1.0;
//  Vec            x;

	std::cout << "PetscInitialize" << std::endl;
	MPI_Comm_size(PETSC_COMM_WORLD, &size);
	MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
	std::cout << "Nada sera construido (" << rank << "," << size << ")" << std::endl;
	create_unit<ParallelVec>();
	std::cout << "Nada construido" << std::endl;
	std::cout << "Finalize" << std::endl;
  ierr = PetscFinalize();CHKERRQ(ierr);
	MPI_Finalize();	
  return 0;
}
 
