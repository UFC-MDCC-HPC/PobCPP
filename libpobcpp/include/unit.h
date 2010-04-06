#ifndef __UNIT__
#define __UNIT__

#include <typeinfo>

#include "unit_type.h"

namespace Pobcpp {

class Unit {
public:

    /**
     * Default constructor.
     */
    Unit();

    /**
     * Simple constructor.
     * @param _global_rank
     */
    Unit(int _global_rank);

    /** 
     * Destructor
     */
    virtual ~Unit();
   
    /**
     * Getter to global_rank
     */
    int get_global_rank(void) const;

    /**
     * Setter to global_rank
     * @param _global_rank
     */
    void set_global_rank(int _global_rank);
		
		virtual void main() = 0;
private:
    int global_rank;
};

template<class ParallelObject, class Unit>
void create_unit(Unit* _created_unit);

template<typename TypePObject, typename TypeUnit>
void create_unit(Unit* _created_unit) {
	boost::mpi::communicator world;

	// Exchange with others units, each rank.
	TypeUnit* typeunit;
	Unit_Type unit_type(typeid(typeunit).name());
	set_global_rank(world.rank());
//	world.allgather(...); // send the tuple<unit_type,world.rank()>
	// Check if everybody is ok and
	// Construct comm object with each type and rank.
}

}

#endif

