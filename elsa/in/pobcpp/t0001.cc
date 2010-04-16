class Pob_Type_Array { 
	public:
	Pob_Type_Array(int a) { }
	template<typename Type>
		void add_type(unsigned int _i) {
		}

};
class A {
	Pob_Type_Array func() { 
		Pob_Type_Array pobtypes(5);
		pobtypes.add_type<int>(42);
		return pobtypes;
	}
	unit B {};
	unit C {};
};

class D {
	unit X { };
};
