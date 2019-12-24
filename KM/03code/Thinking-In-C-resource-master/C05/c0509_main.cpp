#include <iostream>
#include "c0509.h"

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
	Stash henStash;
	Hen h;
	Hen::Nest n;
	Hen::Nest::Egg e;

	henStash.initialize(sizeof(Hen));
	henStash.add((void*)&h);
	henStash.add((void*)&n);
	henStash.add((void*)&e);

	((Hen*) henStash.fetch(0))->display();	
	((Hen::Nest*) henStash.fetch(0))->display();	
	((Hen::Nest::Egg*) henStash.fetch(0))->display();	

}
