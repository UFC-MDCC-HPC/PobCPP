namespace Pobcpp {



class Unit {


};

class Pob_Type_Array { 
	public:
	Pob_Type_Array(int a) { }
	template<typename Type>
		void add_type(unsigned int _i, unsigned int _enum=0) {
		}

};

}


class A { };

class B {


	int no_error;

	unit Normal{};

	unit Enumerated1 [i:n] { };

	unit Enumerated15 [i:n]{ };

	unit   Enumerated2       [i:n] [j:m]  [k:p] { };

	unit        Enumerated    [i : n ] [j:m]  [k:p] { };

/*unit EnumeratedError [i:n]
	[j:m] 
	[k:p]
	{ };

	unit EnumeratedTwice [i:n] [j:m] { };

	unit EnumeratedNumberTwo [i:n] : public A { };

	unit C : public A { };	unit D { };	unit E {

	};

	unit F;

	unsigned int mazela;*/
}; //unit B::C d;

int main() {

	//unit B::C a;

}

