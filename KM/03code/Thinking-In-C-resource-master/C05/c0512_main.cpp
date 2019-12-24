#include <iostream>
#include "c0512.h"

using namespace std;

class Hen{
	public:
		class Nest{
			public:
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
	Hen h;
	Hen::Nest n;
	Hen::Nest::Egg e;

	Stack henStack;

	henStack.push((void*)&h);
	henStack.push((void*)&n);
	henStack.push((void*)&e);

	((Hen*)henStack.pop())->display();
	((Hen::Nest*)henStack.pop())->display();
	((Hen::Nest::Egg*)henStack.pop())->display();
}
