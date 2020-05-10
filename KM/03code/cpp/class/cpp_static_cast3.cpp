#include <iostream>
using namespace std;

#include <iostream>
#include <string>
class A {
public:
  // void method() { cout << "Method A" << endl; }
  virtual void method() { cout << "Method A" << endl; }
  virtual  ~A(){}
};

class B : public A {
public:
  void method() { cout << "Method B" << endl; }
};

struct AA { virtual ~AA(){}};
struct BB {virtual ~BB(){}};

void test() {
  AA *a = new AA;
  //BB *b1 = (BB *)a; // compiles! 强制转换不做类型检测 BU安全
  
  
   // BB *b2 = static_cast<BB *>(a);    安全
  // Fails to compile: static_cast from 'AA *' to 'BB *', which are not related
  // by inheritance, is not allowed

   BB *bptr2 = dynamic_cast<BB*>(a); //  不用的类型转换竟然没有报错
    // cannot dynamic_cast ‘a’ (of type ‘struct AA*’) to type ‘struct BB*’ (source type is not polymorphic)
    if (bptr2 ==NULL)
    {
       cout<< "failed" <<endl; //runtime
    }
    
}
int main() {

  test();
  A a;
  B *pb = new B();
  A *pa = pb;
  
  B *bptr1 = static_cast<B *>(&a);

  bptr1->method();


  try
  {
    //B *bptr2 = dynamic_cast<B*>(&a); // //Segmentation fault (core dumped)
    B *bptr2 = dynamic_cast<B*>(pa); // 
    //B *bptr2 = dynamic_cast<B*>(&pa); //为什么不做类型检测，用户无用错误
    cout << "2" << endl;
    if (bptr2 ==NULL)
    {
        cout<< "B *bptr2 = dynamic_cast<B *>(&a); error" <<endl;
        return 1;
    }
    bptr2->method(); //Segmentation fault (core dumped)
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  

  return 0;
}
/***
 * 若转型失败且 新类型 是指针类型，则它返回该类型的空指针。
 * 若转型失败且 新类型 是引用类型，则它抛出与类型 std::bad_cast 的处理块匹配的异常。
 * 
 * 若 表达式 是到多态类型 Base 的指针或引用，且 新类型 是到 Derived 类型的指针或引用，则进行运行时检查：
a) 检验 表达式 所指向/标识的最终派生对象。若在该对象中 表达式 指向/指代 Derived 的公开基类，且只有一个 Derived 类型对象从 表达式 所指向/标识的子对象派生，则转型结果指向/指代该 Derived 对象。（此之谓“向下转型（downcast）”。）
b) 否则，若 表达式 指向/指代最终派生对象的公开基类，而同时最终派生对象拥有 Derived 类型的无歧义公开基类，则转型结果指向/指代该 Derived（此之谓“侧向转型（sidecast）”。）
c) 否则，运行时检查失败。若 dynamic_cast 用于指针，则返回 新类型 类型的空指针值。若它用于引用，则抛出 std::bad_cast 异常。
 **/