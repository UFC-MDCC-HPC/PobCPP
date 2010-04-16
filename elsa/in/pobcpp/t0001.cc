class Pob_Type_Array { 
	public:
	Pob_Type_Array(int a) { }
	template<typename Type>
		void add_type(unsigned int _i) {
		}

};
class A {
	void func() { 
		Pob_Type_Array pobtypes(5);
		pobtypes.add_type<int>(42);
	}
	unit B {};
	unit C {};
};
