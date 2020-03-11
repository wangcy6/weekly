#include <iostream>

using namespace std;

class CTest
{
	int m_i1;
	void func1();
	public:
	int m_i2;
	void func2();
	protected:
	int m_i3;
	void func3();
	public:
	void ShowMap(CTest* t)
	{
		cout<<"private m_1      = "<<(long)&t->m_i1<<endl;
		cout<<"public  m_2      = "<<(long)&t->m_i2<<endl;
		cout<<"protected  m_3   = "<<(long)&t->m_i3<<endl;
	}
};

int main()
{

	CTest t1;

	t1.ShowMap(&t1);
}
