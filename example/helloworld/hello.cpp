//#include "pobcpp.h"
#include <iostream>

class HelloWorld {
	public:
	unit World;
	unit Hello;
	unit Hello {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			comm.send(!rank, 1, "Hello");
			std::string value;
			comm.recv(!rank, 1, value);
			std::cout << value << std::endl;
			unsigned int* ranks;
			unsigned int size  = ranksof(HelloWorld::World, ranks);
			std::cout << ranks[0] << std::endl;
			std::cout << rank << " func() end" << std::endl;
		}
	};

	unit World {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			if(rank > 1) {
			unsigned int* ranks;
			unsigned int size  = ranksof(void, ranks);
				std::cout << "I'm " << rank << " but I wont participate." << std::endl;
				return;
			}
			std::string value;
			comm.recv(!rank, 1, value);
			comm.send(!rank, 1, "World");
			std::cout << value << std::endl;
			unsigned int* ranks;
			unsigned int size = ranksof(HelloWorld::Hello, comm, ranks);
			//unsigned int* ranks  = ranksof(HelloWorld::World);
			std::cout << ranks[0] << std::endl;
			std::cout << rank << " func() end" << std::endl;
		}
	};

};
int main(int argc, char** argv) { 
	MPI_Init(&argc, &argv);
	Communicator comm;
	std::cout << "My rank:" << comm.rank() << std::endl;
	unit HelloWorld::Hello h;
	unit HelloWorld::World w;
	if(comm.rank() == 0)
		h.func(comm);
	else
		w.func(comm);
	MPI_Finalize();
}
