#include <iostream>
#include "pob_macro.h"

int main (int argc, char* argv[]) {

    pob_init;
    POb pob;
		std::cout << "==" << world.rank() << "==" << "Parallel Object constructed " << std::endl;
    barrier;
    pob.main ();
    std::cout << "--------- " << world.rank() <<  std::endl;

    return 0;
}
