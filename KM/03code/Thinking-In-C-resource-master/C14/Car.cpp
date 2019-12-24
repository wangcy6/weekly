class Engine{
	public:
		void start() const {}
		void stop() const {}
		void rev() const {}
};


class Wheel{
	public:
		void inflate(int psi) const {}
};

class Window{
	public:
		void rollup() const {}
		void rolldown() const {}
};

class Door{
	public:
		Window window;
		void open() const {}
		void close() const {}
};

class Car{
	public:
		Engine e;
		Wheel wheel[4];
		Door left, right;
};

int main()
{
	Car car;
	car.left.window.rollup();
	car.wheel[0].inflate(72);
}
