// #include directives
//

class Parallel_Object { // parallel_class
public:
    Parallel_Object (void);
    ~Parallel_Object (void);
    
    unit master { // unit_master 
	parallel void compute (void);
    }

    unit A { // unit (A) 
	parallel void compute (void);
    }

    unit B { // unit (B)
	parallel void compute_other_thing (void);
    }



private:



}
