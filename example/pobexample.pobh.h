#ifndef __BLAH__
#define __BLAH__
template<typename Type>
void func2() {
	Type::func();
}

class Etc {
	static void func() {

	}
};

class HelloWorld {
	public:
	unit World;
	unit Hello {
		public:
		Hello();
	//	void sendHello();
		void sendHello() {
			comm->send<HelloWorld::World>(42, 1);
			int data = 45;
			comm->broadcast<Hello>(data);
		}

	};

	unit World {
		public:
		World();
		int recvHello();

	};
	static int func() { }	

	public: static Pobcpp::Pob_Type_Array __get_types() { Pobcpp::Pob_Type_Array pobtypes(2); pobtypes.add_type<Hello>(0);pobtypes.add_type<World>(1);;return pobtypes; } private:}; //	};
	};

#endif
