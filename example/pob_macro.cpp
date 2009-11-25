#include "pob_macro.h"

#include <iostream>

boost::mpi::communicator POb::world;

POb::POb(void){ 
	env.add<unit(B)>(); 
	env.add<unit(A)>(); 
	env.init();
}

int POb::main(void) {
}

void POb::unit(A)::main(void) {
	compute();	
}

void POb::unit(A)::compute (void) {
	std::cout << "==" << world.rank() << "==" << "A sent 10" << std::endl;
	comm.send<unit (B)>(10,1);
}


void POb::unit(B)::compute_other_thing (void) {
	std::cout << "==" << world.rank() << "==" << "B getting" << std::endl;
	int get = comm.receive<unit (A),int>(1);
	std::cout << "==" << world.rank() << "==" << "got: " << get << std::endl;

}

void POb::unit(B)::main (void) {
	compute_other_thing();
}

