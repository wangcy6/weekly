#include "iostream"
#include <typeinfo>
using namespace std;


class Base{
	public:
		Base(){
			cout<<typeid(this).name()<<endl;
			cout << "Base::Base()\n";
			fun();
		}
		virtual ~Base(){
			cout << "Base::~Base()\n";
			fun();
		}
		virtual void fun(){
			cout << "Base::fun() virtual\n";
		}
};

// 派生类
class Derive: public Base{
	public:
		Derive(){
			cout<<typeid(this).name()<<endl;
			cout << "Derive::Derive()\n";
			fun();
		}
		~Derive(){
			cout << "Derive::~Derive()\n";
			fun();
		}
		virtual void fun(){
			cout << "Derive::fun() virtual\n";
		}
		
    };
	


int main(){
	
	
	
	Base *b = new Base();
	delete b;
	cout << "-----------------------------------\n";
	Derive *d = new Derive();
	delete d;
	cout << "-----------------------------------\n";
	Base *bd = new Derive();  // 基类Base的指针bd指向的是派生类Derive的对象
	delete bd;
	cout << "-----------------------------------\n";
	Derive d;
	return 0;
}
/**
P4Base
Base::Base()
Base::fun() virtual
Base::~Base()
Base::fun() virtual
-----------------------------------
P4Base
Base::Base()
Base::fun() virtual
P6Derive
Derive::Derive()
Derive::fun() virtual
Derive::~Derive()
Derive::fun() virtual
Base::~Base()
Base::fun() virtual
-----------------------------------
P4Base
Base::Base()
Base::fun() virtual
P6Derive
Derive::Derive()
Derive::fun() virtual
Derive::~Derive()
Derive::fun() virtual
Base::~Base()
Base::fun() virtual
**/
