#include <iostream>

class HelloWorld {
	public:
	unit World;
	unit Hello;
	unit Hello {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			int* ranks;
			unsigned int size  = ranksof(HelloWorld::Hello, ranks);
			Group grp = comm.group();
			Group newgroup = grp.include(size, ranks);
			Communicator newcomm = comm.create(newgroup);
			std::cout << "[Rank] " << std::endl;
			for(unsigned int i = 0; i < size; i++)
				std::cout << ranks[i] << " ";
			std::cout << std::endl << "[/Rank] " << std::endl;
			std::cout << "Old rank: " << comm.rank() << "," << newcomm.rank() << std::endl;
			std::cout << rank << " func() end" << std::endl;
		}
	};

	parallel unit World {
		public:
		void func() [Communicator comm] {
			int rank = comm.rank();
			/*if(rank > 1) {
			int* ranks;
			unsigned int size  = ranksof(void, ranks);
				std::cout << "I'm " << rank << " but I wont participate." << std::endl;
				return;
			}*/
			int* ranks;
			unsigned int size = ranksof(HelloWorld::World, comm, ranks);
			Group grp = comm.group();
			Group newgroup = grp.include(size, ranks);
			Communicator newcomm = comm.create(newgroup);
//			Group group;
//			group.
			//int* ranks  = ranksof(HelloWorld::World);
			std::cout << "[Rank] " << std::endl;
			for(unsigned int i = 0; i < size; i++)
				std::cout << ranks[i] << " ";
			std::cout << std::endl << "[/Rank] " << std::endl;
			std::cout << "Old rank: " << comm.rank() << "," << newcomm.rank() << std::endl;
			int a = (comm.rank()+1)*newcomm.rank();
			int b = a;
			newcomm.broadcast(a, 2);
			std::cout << "bcast-bf: " << b << " / bcast: " << a << std::endl;
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
