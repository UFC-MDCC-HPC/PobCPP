#include "unit_type.h"
#include "unit.h"

class HelloWorld {
	public:
	unit World;
	unit Nothing;
	unit Hello {
		public:
		void sendHello() {
			comm->send<HelloWorld::World>(42, 1);
		}

	};

	unit World {
		public:
		int recvHello() {
			comm->receive<HelloWorld::Hello, int>(1);
			comm->receive<HelloWorld::Nothing, int>(0,2);
		}

	};
	unit Nothing [i:n] {
		public:
		Nothing(unsigned int i, unsigned int n) : i(i), n(n) { }
		void doNothing() {
			comm->send<HelloWorld::World>(43,2);
		}
	};
	

};
