namespace Pobcpp {

class Unit {


};

class Pob_Type_Array { 
	public:
	Pob_Type_Array(int a) { }
	template<typename Type>
		void add_type(unsigned int _i, unsigned int _enum = 0) {
	}

};
}
class A {
	Pobcpp::Pob_Type_Array func() { 
		Pobcpp::Pob_Type_Array pobtypes(5);
		pobtypes.add_type<int>(42);
		pobtypes.add_type<double>(42,2);
		return pobtypes;
	}
	unit B {};
	unit C {};
	unit E [i:j] { };
};


