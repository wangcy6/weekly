#include "iostream"
#include <typeinfo>
using namespace std;

/**
多继承（Multiple Inheritance，MI）是C++特有的概念
https://cs.nyu.edu/courses/fall16/CSCI-UA.0470-001/slides/MemoryLayoutMultipleInheritance.pdf
http://cplusplus-development.blogspot.com/2013/09/memory-layout-for-multiple-and-virtual.html
https://shaharmike.com/cpp/vtable-part3/
**/

class Base {
protected:
  int value;

public:
  Base() { cout << "in Base" << endl; }
};

class DerivedA : public virtual Base {
public:
  DerivedA() { cout << "in DerivedA" << endl; }
};
class DerivedB : public virtual Base {
public:
  DerivedB() { cout << "in DerivedB" << endl; }
};

class MyClass : public DerivedA, public DerivedB {
public:
  MyClass() { cout << "in MyClass" << endl; }
};

class Top {
public:
  int a;
  //重要在什么地方
  virtual ~Top() {}
};

class Left : virtual public Top {
public:
  int b;
};

class Right : virtual public Top {
public:
  int c;
};
class Bottom : public Left, public Right {
public:
  int d;
};
//多继承
class Top1 {
public:
  int a;
};
class AnotherBottom : public Left, public Right {
public:
  int e;
  int f;
};
class Left1 : public Top1 {
public:
  int b;
};

class Right1 : public Top1 {
public:
  int c;
};
class Bottom1 : public Left1, public Right1 {
public:
  int d;
};

void test1() {
  MyClass *myclass = new MyClass();
  cout << "sizeof(int) =" << sizeof(int) << " sizeof(*int) =" << sizeof(int *)
       << endl;                                             // 4  4
  cout << "sizeof(Base) =" << sizeof(Base) << endl;         // 4  4
  cout << "sizeof(DerivedA) =" << sizeof(DerivedA) << endl; // 4 16
  cout << "sizeof(DerivedB) =" << sizeof(DerivedB) << endl; // 4  16
  cout << "sizeof(MyClass)=" << sizeof(myclass) << endl;    // 8  24

  cout << "sizeof(Top) =" << sizeof(Top) << endl;      //  4
  cout << "sizeof(Left) =" << sizeof(Left) << endl;    // 16
  cout << "sizeof(Right) =" << sizeof(Right) << endl;  //  16
  cout << "sizeof(Bottom)=" << sizeof(Bottom) << endl; // 40
}
/*
  test_inheritance
  bottom =0xf8d010
  left1=0xf8d010
  right1=0xf8d020
  top2=0xf8d030
*/
void test_inheritance() {

  Bottom1 *bottom = new Bottom1();
  Right1 *right1 = bottom;
  Left1 *left1 = bottom;
  // If you cast to B1 first and then R it is legal - you have disambiguated
  cout << "test_inheritance" << endl;

  Top1 *top2 = bottom; // https://my.oschina.net/u/2461850/blog/1603690
  cout << "bottom =" << bottom << " left1=" << left1 << " right1=" << right1
       << "top2=" << top2 << endl;
  // old gcc error: `Top' is an ambiguous base of `Bottom'
  // Top* topL = (Left*) bottom;
  // An ambiguous base class is a base class that is included in a derived class
  // twice
  // http://hacksoflife.blogspot.com/2007/03/c-objects-part-6-ambiguous-base-classes.html

  // https://zh.cppreference.com/w/cpp/language/static_cast
  /*
   A static cast from D to R is illegal because it is ambiguous. Do we want R
   via B1 or B2? We don't know, and because the cast is static the compiler
   knows we don't know at compile time and generates an error.
https://hacksoflife.blogspot.com/2007/04/c-objects-part-7-dynamic-casts-and.html
  */
  /** 理论啥意思，有什么作用呢？
   *  1、static_cast:可以实现C++中内置基本数据类型之间的相互转换，enum、struct、 int、char、float等。
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
   *
 
   *
   *
   *

   **/
  cout << " bottom=" << bottom << " top2=" << top2 << endl;
}

// https://zh.cppreference.com/w/cpp/language/copy_assignment
void test_virtual_inheritance() { // https://my.oschina.net/feistel/blog/3000199

  Bottom *bottom = new Bottom();

  cout << "test_virtual test upcast " << endl;
  // upcast
  Left *left = bottom;
  Right *right = bottom;
  cout << "bottom=" << bottom << " left=" << left << " righ=" << right << endl;
  cout << "left->a=" << &(left->a) << " right->a=" << &(right->a) << endl;

  cout << "test_virtual test Downcasting ................ " << endl;

  Bottom *bottom1 = new Bottom();
  // AnotherBottom *bottom1 = new AnotherBottom();
  // Top *top1 = bottom1; // 0k
  Top *top1 = static_cast<Top *>(bottom1);

  // Now consider how to implement the static cast from top1 to left1(中间层)
  // while taking into account that we do not know whether top1 is
  // pointing to an object of type Bottom or an object of type AnotherBottom. It
  // can't be done!

  // why compiler error : cannot convert from
  // Left *left3 = static_cast<Left *>(top2);
  // Left *left1 = static_cast<Left *>(top1); //why error
  // Left *left2 = (Left *)(top1); //why error

  // why error: cannot dynamic_cast ‘top1’ (of type ‘class Top*’) to type ‘class Left*’ 
  // 
  //
  //
  //
  //
  //
  //
  //
  //  (source type is not polymorphic)

  Left *left2 =
      dynamic_cast<Left *>(top1); // top1 现在指向的谁  dynamic_cast 如何知道
  //
  //
  // The problem is that a dynamic cast (as well as use of typeid) needs runtime
  // type information about the object pointed to by top1.
  // add virtual ~Top()
  // dynamic_cast
}

// 1. Copy constructor vs assignment operator in C++
// ref
// https://isocpp.org/wiki/faq/assignment-operators

void test_assignment_operaotr() {}
int main() {
  test_inheritance();
  test_virtual_inheritance();
  return 0;
}
