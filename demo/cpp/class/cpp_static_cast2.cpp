#include <iostream>
using namespace std;

#include <iostream>
#include <string>
class B {
public:
  virtual ~B() {}
};
class D : public  B {};
//class D : public virtual B {};
class X {};
int main() {
  D *d = new D;
  B *pb = d;
  D *pd = static_cast<D *>(pb); //有虚继承 向下转换 static完蛋
  // https://en.cppreference.com/w/cpp/language/static_cast

  return 0;
}

//https://www.oschina.net/translate/cpp-virtual-inheritance?print
