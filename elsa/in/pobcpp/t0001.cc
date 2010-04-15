class Pob_Type_Array { 
	Pob_Type_Array(int a) { }
	template<typename Type>
		void add_type(unsigned int _i) {
	//		Unit_Type type(Type*);
	//		types[_i] = type;
		}

};
class A {
	void func() { 
		Pob_Type_Array pobtypes(5);
		pobtypes.add_type<int>(3);
		pobtypes.add_type<float>(2);
	}
	unit B {};
	unit C {};
};
