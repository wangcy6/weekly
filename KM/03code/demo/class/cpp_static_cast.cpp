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

struct DD : private B {};

struct D1 : B {};
struct D2 : B {};

void test_errinput() {
  B *p = new D1;
  D2 *p1 = static_cast<D2 *>(p); // undefined behavior, no D2 object here
}

void f() {
  DD *p = static_cast<DD *>((B *)0); // error: B is a private base of D
  // http://eel.is/c++draft/expr.static.cast#11
}
int main() {
  D *d = new D;
  B *b = static_cast<B *>(d);   // this works
                                //编译阶段确定错误
  X *x = static_cast<X *>(d);   // ERROR - Won't compile
  X *x1 = dynamic_cast<X *>(d); //

  B a;
  D *ptr1 = static_cast<D *>(&a); //"It's undefined behavior."

  D *ptr2 = dynamic_cast<D *>(&a);

  return 0;
}