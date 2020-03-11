#include <fstream>
using namespace std;

class Base{
	int i;
	protected:
	int read() const {return i;}
	void set(int ii) {i = ii;}
	public:
	Base(int ii = 0): i(ii) {}
	int value(int m) const {
	return m*i;
	}
};

class Derived: public Base{
	int j;
	public:
	Derived(int jj = 0): j(jj){}
	void change(int x) { set(x); }
};

int main()
{
	Derived d;
	d.change(10);
	return 0;
}
