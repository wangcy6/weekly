#include <iostream>

using namespace std;

class C_1;
class C_2;
class C_3
{
	public:
	void printf(C_1* s);
};


class C_1
{
	int data;
	friend class C_2;
	friend void C_3::printf(C_1* s);
	public:
	void setdata(int  i);
};

class C_2{
	public:
		void printf(C_1* s);
};

void C_1::setdata(int ival)
{
	data = ival;
}

void C_2::printf(C_1* s)
{
	cout<<"C_2::pritnf()   C_1.data = "<< s->data<<endl;
}

void C_3::printf(C_1* s)
{
	cout<<"C_2::printf()   C_1.data = "<< s->data<<endl;
}

int main()
{
	C_1 c1;
	C_2 c2;
	C_2 c3;

	c1.setdata(12);
	c2.printf(&c1);
	c3.printf(&c1);
}
