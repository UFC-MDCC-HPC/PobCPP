class HelloWorld {
	public:
	unit World;
	unit Nothing;
	unit Hello {
		public:
		Hello();
		void sendHello();

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
