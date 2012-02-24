class A { };

class B {

	unit C : public A  ,virtual public Pobcpp::Unit { };	 //	unit C : public A { };	
	unit D  : virtual public Pobcpp::Unit { };	 //	unit D { };	

	unit E  : virtual public Pobcpp::Unit { //	unit E {

	};

	class F; //	unit F;
}; 
class B::C d; //unit B::C d;

class G {

	unit L [i:n]  : virtual public Pobcpp::Unit {}; //	unit L [i:n] {};
	unit J  : virtual public Pobcpp::Unit { }; //	unit J { };

};

int main() {

	class B::C a; //	unit B::C a;

}
