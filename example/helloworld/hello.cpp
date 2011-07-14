#include "pobcpp.h"
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
			unsigned int* ranks  = ranksof(HelloWorld::World);
			std::cout << ranks[0] << std::endl;
		}
	};

	unit World {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			std::string value;
			comm.recv(!rank, 1, value);
			comm.send(!rank, 1, "World");
			std::cout << value << std::endl;
			//unsigned int* a = ranksof(HelloWorld::Hello);
			unsigned int* ranks  = ranksof(HelloWorld::World);
			std::cout << ranks[0] << std::endl;
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
