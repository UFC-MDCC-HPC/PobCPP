#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

#define synchronous_channel \
	Pobcpp::Synchronous_Channel

#define pob_init	\
	boost::mpi::environment env(argc, argv);	\
	boost::mpi::communicator world;

#define barrier world.barrier ()

