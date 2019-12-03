#include <iostream>
using namespace std;

#include <iostream>
#include <string>
class A {
public:
  void method() { cout << "Method A" << endl; }
};

class B : public A {
public:
  void method() { cout << "Method B" << endl; }
};
int main() {
  A a;
  B *bptr = static_cast<B *>(&a);
  bptr->method();
  return 0;
}