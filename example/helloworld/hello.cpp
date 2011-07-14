#include "pobcpp.h"
#include <iostream>
class HelloWorld {
	public:
	unit Hello {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			comm.send(!rank, 1, "Hello");
		}
	};

	unit World {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			std::string value;
			comm.recv(!rank, 1, value);
			std::cout << value << std::endl;
		}
	};

};
int main(int argc, char** argv) { 
	MPI_Init(&argc, &argv);
	Communicator comm;
	std::cout << "My rank:" << comm.rank() << std::endl;
	unit HelloWorld::Hello h;
	unit HelloWorld::World w;
	h.func(comm);
	w.func(comm);
	MPI_Finalize();
}
