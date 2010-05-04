#include "unit_type.h"
#include "unit.h"

class HelloWorld {
	public:
	unit World;
	unit Hello {
		public:
		void sendHello() {
			comm->send<HelloWorld::World>(42, 1);
		}

	};

	unit World {
		public:
		int recvHello() {
			return comm->receive<HelloWorld::Hello, int>(1);
		}

	};

	

};
