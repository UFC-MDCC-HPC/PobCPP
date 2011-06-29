class A {

	unit B {
	};

	unit C {
		void func() [Commd comm] { }
	};
};

int main() {

	ranksof(A::B);
}


