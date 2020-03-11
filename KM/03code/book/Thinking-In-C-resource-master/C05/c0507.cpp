#include <iostream>

using namespace std;

class Hen{
	private:
		int data;
	public:
		class Nest;
//		friend Nest;
		//class Egg;
		//friend Egg;

		class Nest{
			int data;
		public:
			class Egg;
			friend Egg;
			friend Hen;
			class Egg{
				private:
					int	data;
				public:
					friend Hen;
					friend Nest;
					void display();
			};
			void display();
			void initNest(Nest* n)
			{
				n->data = 2;
			}
		};
		void display();
		void initHen(Hen* h)
		{
			h->data = 1;
		}
};


void Hen::Nest::display()
{
	cout<<"Nest display()"<<endl;
}
void Hen::Nest::Egg::display()
{
	cout<<"Egg display()"<<endl;
}

void Hen::display()
{
	cout<<"Hen display()"<<endl;
//	Nest *nest;
//	nest->data = 2;
//	Egg* egg;
//	egg->data  = 3;
//	cout<<"Nest data = "<<nest->data<<endl;
//	cout<<"Egg data =  "<<egg->data<<endl;
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
