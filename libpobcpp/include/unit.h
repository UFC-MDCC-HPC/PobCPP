#ifndef __UNIT__
#define __UNIT__

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


}

#endif

