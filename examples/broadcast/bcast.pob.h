#include "unit_type.h"
#include "unit.h"

class Bcast_Example {
	public:
	unit Example;
	unit Receiver {
		public:
			Receiver();
			void doBcast() {
				int value = -1;
				comm->broadcast<Receiver>(value);
				std::cout << "Value received " << value << std::endl;
			}
	};



	unit Example {
		public:
		void doBcast() {
			int value = 45;
			comm->broadcast<Receiver>(value);
		}
	};
	

};
