#include <iostream>
using namespace std;

#include <iostream>
#include <string>
class B {
public:
  virtual ~B() {}
};
// class D : public  B {};
class D : public virtual B {};

class X {};
struct D1 : B {};
struct D2 : B {};

void test_errinput() {
  B *p = new D1;
  D2 *p1 = static_cast<D2 *>(p); // undefined behavior, no D2 object here
}


int main() {
  D *d = new D;
  B *b = static_cast<B *>(d);   // up this works 


                                //编译阶段确定错误
  // X *x = static_cast<X *>(d);   // ERROR - Won't compile
  // X *x1 = dynamic_cast<X *>(d); // runtime error

  B a;
  D *ptr1 = static_cast<D *>(&a); //  error down
  //https://zh.cppreference.com/w/cpp/language/static_cast
  // D *ptr2 = dynamic_cast<D *>(&a);

  return 0;
}