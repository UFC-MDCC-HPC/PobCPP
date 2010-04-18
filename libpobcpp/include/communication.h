#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/collectives.hpp>

#define pob_init	\
	boost::mpi::environment __env(argc, argv);	\
	boost::mpi::communicator world;

#define barrier world.barrier ()

