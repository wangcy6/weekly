class Pet{
	public:
		char eat() const { return 'a';}
		int speak() const { return 2; }
		float sleep() const {return 3.0;}
		float sleep(int) const {return 4.0;}
};

class Goldfish: Pet {
	public:
		using Pet::eat;
		using Pet::sleep;
};

int main()
{
	Goldfish bob;
	bob.eat();
	bob.sleep();
	bob.sleep(1);
	//bob.speak();
}
