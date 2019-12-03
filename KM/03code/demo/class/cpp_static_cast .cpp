#include <iostream>
using namespace std;

#include <iostream>
#include <string>
class A {
public:
  // void method() { cout << "Method A" << endl; }
  virtual void method() { cout << "Method A" << endl; }
};
struct AA {};
struct BB {};

class B : public A {
public:
  void method() { cout << "Method B" << endl; }
};

void test() {
  AA *a = new AA;
  BB *b1 = (BB *)a; // compiles!
  // BB *b2 = static_cast<BB *>(a);
  // Fails to compile: static_cast from 'AA *' to 'BB *', which are not related
  // by inheritance, is not allowed
}
int main() {
  A a;
  B *pb = new B();
  A *pa = pb;
  B *bptr1 = static_cast<B *>(&a);

  bptr1->method();

  B *bptr2 = dynamic_cast<B *>(&a);
  cout << "2" << endl;
  bptr2->method();

  return 0;
}