class HelloWorld {
	public:
	unit World;
	unit Nothing;
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
	unit Nothing [i:n] {
		public:
		Nothing(unsigned int i, unsigned int n);
		void doNothing();
	};
	

};
