class HelloWorld {
	public:
	unit World;
	unit Nothing;
	unit Hello {
		public:
		void sendHello();

	};

	unit World {
		public:
		int recvHello();

	};
	unit Nothing [i:n] {
		public:
		Nothing(unsigned int i, unsigned int n) : i(i), n(n) { }
		void doNothing();
	};
	

};
