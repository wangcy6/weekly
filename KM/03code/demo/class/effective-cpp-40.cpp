#include "iostream"
#include <typeinfo>
using namespace std;

/**
多继承（Multiple Inheritance，MI）是C++特有的概念
**/
//https://cloud.tencent.com/developer/article/1022274
//https://www.oschina.net/translate/cpp-virtual-inheritance
//https://www.bbsmax.com/A/QV5ZLYlnzy/
class Base
{
protected:
	 int value;
 public:
	 Base()
	 {
	 cout<<"in Base"<<endl;
	 }
 };
 
 class DerivedA:public  virtual  Base
 {
 public:
	DerivedA()
	{
	cout<<"in DerivedA"<<endl;
	}
 };
 class DerivedB: public virtual  Base
 {
 public:
	DerivedB()
	{
	 cout<<"in DerivedB"<<endl;
	}
 };

 class MyClass:public DerivedA,public DerivedB
 {
 public:
	MyClass()
	{
	  cout<<"in MyClass"<<endl;
	}
 };
 
 class Top
{ 
 public: int a;
}; 

class Left : virtual public Top
{ 
  public: int b;
}; 

class Right : virtual public Top
{ public: int c;
}; 
class Bottom : public Left, public Right
{ public: int d;
};


 class Top1
{ 
 public: int a;
}; 

class Left1 : public Top1
{ 
  public: int b;
}; 

class Right1 :  public Top1
{ public: int c;
}; 
class Bottom1 : public Left1, public Right1
{ public: int d;
};

void test1()
{  
   MyClass* myclass =new MyClass();
   cout<< "sizeof(int) ="<<sizeof(int)<<" sizeof(*int) ="<<sizeof(int*)<<endl; //4  4 
   cout<< "sizeof(Base) ="<<sizeof(Base)<<endl; //4  4
   cout << "sizeof(DerivedA) ="<<sizeof(DerivedA)<<endl;//4 16
   cout << "sizeof(DerivedB) ="<<sizeof(DerivedB)<<endl;//4  16
   cout << "sizeof(MyClass)=" <<sizeof(myclass)<<endl;	//8  24
   
   cout<< "sizeof(Top) ="<<sizeof(Top)<<endl; //  4
   cout << "sizeof(Left) ="<<sizeof(Left)<<endl;// 16
   cout << "sizeof(Right) ="<<sizeof(Right)<<endl;//  16
   cout << "sizeof(Bottom)=" <<sizeof(Bottom)<<endl;	//40
}

void test_type()
{  //https://my.oschina.net/feistel/blog/3000199
	Bottom* pb =new Bottom();
	
	Top* pt =(Top*)pb;
	cout<<pt->a<<endl;
	
	Bottom* bottom1 = new Bottom();
	Top* top1 = bottom1;
	//https://www.oschina.net/translate/cpp-virtual-inheritance
	//Left* left1 = static_cast<Left*>(top1); //downcast
	//Left* left2 = static_cast<Left*>(bottom1); //upcast
	Left* left3 = dynamic_cast <Left*>(top1)
	// error: cannot dynamic_cast ‘top1’ (of type ‘class Top*’) to type ‘class Left*’ (source type is not polymorphic)

	
}
void test_no_virtual()
{
	Bottom1* bottom = new Bottom1();
	Left1* left = bottom;
	Right1* right = bottom;




}

int main()
{
    test_no_virtual();
  
    //test1();
    //test_type();
	
	return 0;
}
/**
"Inside the C++ Object Model
 how multiple and virtual inheritance is achieved via the vtables.
 https://stackoverflow.com/questions/28521242/memory-layout-of-a-class-under-multiple-or-virtual-inheritance-and-the-vtables/28521423
https://cs.nyu.edu/courses/fall16/CSCI-UA.0470-001/slides/MemoryLayoutMultipleInheritance.pdf
**/
