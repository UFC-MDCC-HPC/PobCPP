#ifndef __SYNCHRONOUS_CHANNEL__
#define __SYNCHRONOUS_CHANNEL__

#include <boost/mpi/communicator.hpp>

namespace Pobcpp {

/**
 * Synchronous Channel class.
 * 
 */

template<typename Data, typename Unit1, typename Unit2>
class Synchronous_Channel {
public:

    /**
     * Simple contrutctor.
     */
    Synchronous_Channel (void);

    /**
     * Destructor.
     */
    ~Synchronous_Channel (void);

    void connect (int _unit1, int _unit2);

    /**
     * Send function.
     * @param _data
     */
    void send (const Data& _data);

    /**
     * Get function.
     * @return Data sent by other unit.
     */
    Data get (void);

private:
    /* Communicator */
    boost::mpi::communicator world;
    /* Ranks */
    int unit1_rank;
    int unit2_rank;

};

/* 
 * The implementation (definition) of a template class or 
 * function must be in the same file as its declaration. 
 */


template<typename Data,
	 typename Unit1,
	 typename Unit2>
Synchronous_Channel<Data, Unit1, Unit2>::Synchronous_Channel (void) { }

template<typename Data,
	 typename Unit1,
	 typename Unit2>
Synchronous_Channel<Data, Unit1, Unit2>::~Synchronous_Channel (void) { }

template<typename Data,
	 typename Unit1,
	 typename Unit2>
void Synchronous_Channel<Data, Unit1, Unit2>::connect (int _unit1, int _unit2) {
    unit1_rank = _unit1;
    unit2_rank = _unit2;
}
template<typename Data,
	 typename Unit1,
	 typename Unit2>
void Synchronous_Channel<Data, Unit1, Unit2>::send (const Data& _data) { 
    // MPI send...
    world.send(unit2_rank, 0, _data);
}

template<typename Data, typename Unit1, typename Unit2>
Data Synchronous_Channel<Data, Unit1, Unit2>::get (void) {
    // MPI recv
    Data value;
    world.recv(unit1_rank, 0, value);
    return value;
}

}

#endif //__SYNCHRONOUS_CHANNEL__

