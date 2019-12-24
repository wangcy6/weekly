#include <iostream>

using namespace std;

class NoVirtual {
	int a;
	public:
	void x() const { }
	int i() const { 
		return 1;
	}
};


class OneVirtual {
	int a;
	public:
	virtual void x() const {}
	int i() const {
		return 1;
	}
};


class TwoVirtual {
	int a;
	public:
	virtual void x() const {}
	virtual int i() const {
		return 1;
	}
};
//注意内存对齐，所以这里的长度应该是４＋８再加上填充的４字节，所以为１６

int main()
{
	cout<<"int : "<<sizeof(int)<<endl;
	
	cout<<"NoVirtual : "
		<<sizeof(NoVirtual)<<endl;

	cout<<"void* :"<<sizeof(void*)<<endl;
	cout<<"OneVirtual : "
		<<sizeof(OneVirtual)<<endl;
	cout<<"TwoVirtual : "
		<<sizeof(TwoVirtual)<<endl;

}
