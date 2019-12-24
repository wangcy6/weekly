#include <iostream>
using namespace std;

class Clsy2;

class Clsy1{
	int data;
	public:
	friend class Clsy2;
		void func(Clsy2* p);

};

class Clsy2
{
	int data;
	public:
	friend class Clsy1;
	void func(Clsy1* p);

};

void Clsy1::func(Clsy2* p)
{
	p->data = 2;
	cout<<"CLsy2->data = "<<p->data<<endl;
}
void Clsy2::func(Clsy1* p)
{
	p->data = 1;
	cout<<"CLsy1->data = "<<p->data<<endl;
}

int main()
{
	Clsy1 s1;
	Clsy2 s2;

	s1.func(&s2);
	s2.func(&s1);

}
