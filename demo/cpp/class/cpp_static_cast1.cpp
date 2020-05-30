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
int main() {
  D *d = new D;
  B *b = static_cast<B *>(d); // this works up 100%，讨论up没有意义

  X *x = static_cast<X *>(d);   // ERROR - Won't compile
  X *x1 = dynamic_cast<X *>(d); //动态转换依然发现不了这个错误

  return 0;
}