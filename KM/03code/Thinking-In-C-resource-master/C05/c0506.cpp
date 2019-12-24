#include <iostream>

using namespace std;

class Hen{
	public:
		class Nest;
		//	class Egg;

		class Nest{
			public:
				class Egg;
				class Egg{
					public:
						void display();
				};
				void display();

		};
		void display();
};

void Hen::display()
{
	cout<<"Hen display()"<<endl;
}

void Hen::Nest::display()
{
	cout<<"Nest display()"<<endl;
}
void Hen::Nest::Egg::display()
{
	cout<<"Egg display()"<<endl;
}
int main()
{
	Hen hen;
	Hen::Nest nest;
	Hen::Nest::Egg egg;

	hen.display();
	nest.display();
	egg.display();

}
