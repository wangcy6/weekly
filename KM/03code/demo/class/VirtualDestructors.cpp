//: C15:VirtualDestructors.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Behavior of virtual vs. non-virtual destructor
#include <iostream>
using namespace std;

class Base1 {
public:
  ~Base1() { cout << "~Base1()\n"; }
};

class Derived1 : public Base1 {
public:
  ~Derived1() { cout << "~Derived1()\n"; }
};






class Base2 {
public:
  Base2() 
 { 
   //语法上规定构造函数不能声明为虚函数 error: constructors cannot be declared virtual
   //在构造函数内 可以使用虚函数，只是普通函数的无法发挥虚函数作用
   // 子类对象还没有创建完成，如果通过基类指针调用调用虚函数，没有意义，而是无法发挥的多态的作用
 }
  virtual ~Base2() { cout << "~Base2()\n"; 
  // 析构可以是虚函数,假如不声明为虚函数，有什么危害？
  // 场景--通过通过基类指针访问子类时候，如果声明了虚函数，可以触发析正确析构顺序：首先是当前的的类，然后是起基类。
  // 如果没有有定义虚析构函数的话，属于静态绑定，只根据基类这个类型（this）调用对应函数。
  //说明1 ：场景--A通过基类通过引用访问,或者 通过子类访问 不会出现这样问题。正确触发析构
  //说明2 ，先释放子类，在释放基类 ，这个表示不正确，// A B C  删除 B ，不会触发c的
  // 基类不析构不声明为虚函数 通过自己调用，和引用调用 保持正常的修改，但是通过基类访问无法触发。这可能是是一个bug
    //If a class does not contain virtual functions, that often indicates it is not meant to be used as a base class. 
    // When a class is not intended to be a base class, making the destructor virtual is usually a bad idea
  }
};

class Derived2 : public Base2 {
public:
  ~Derived2() { cout << "~Derived2()\n"; }
};

int main() {

  cout<<" no virtual is static "<<endl;
  Base1* bp = new Derived1(); // Upcast  out-of-memory 
  delete bp; // 这是一个bug
  
  Base2* b2p = new Derived2; // Upcast
  delete b2p;
  

  cout<<" ref is ok"<<endl;
  Derived2 dd;
  Base2 &ref =dd;

  cout<<" ref is ok"<<endl;
  Derived2 d3;
  Base2 *p3 =&dd;
  //delete p3;

  Derived1 last;
} 

/**
 * https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
  ~Base1()

   ~Derived2() //自己
   ~Base2() //基类

   ~Derived2()
   ~Base2()
 */