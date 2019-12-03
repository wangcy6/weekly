#include <iostream>
using namespace std;

/**Fqa
 *q1 what is side-cast or cross-cast in Dynamic_cast in C++?
  a1：
    https://stackoverflow.com/questions/35959921/what-is-side-cast-or-cross-cast-in-dynamic-cast-in-c
 * https://en.cppreference.com/w/cpp/language/dynamic_cast
 * https://zh.cppreference.com/w/cpp/language/dynamic_cast

 q2:Call of overloaded static_cast is ambiguous
 https://stackoverflow.com/questions/48914772/call-of-overloaded-static-cast-is-ambiguous

 关键词：多继承模糊基类
 */

#include <iostream>
#include <string>

// Class identifier
enum ClassID {
  BASE,
  DERIVED
  // Others can be added here later
};

class Base {
protected:
  int m_value;

public:
  Base(int value) : m_value(value) {}

  virtual ~Base() {}
  virtual ClassID getClassID() { return BASE; }
};

class Derived : public Base {
protected:
  std::string m_name;

public:
  Derived(int value, std::string name) : Base(value), m_name(name) {}

  std::string &getName() { return m_name; }
  virtual ClassID getClassID() { return DERIVED; }
};
class Derived1 : public virtual Base {
protected:
  std::string m_name;

public:
  Derived1(int value, std::string name) : Base(value), m_name(name) {}

  std::string &getName() { return m_name; }
};
Base *getObject(bool bReturnDerived) {
  if (bReturnDerived)
    return new Derived(1, "Apple");
  else
    return new Base(2);
}

// https://en.cppreference.com/w/cpp/language/static_cast
// https://zh.cppreference.com/w/cpp/language/static_cast
// https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used?rq=1
// https://stackoverflow.com/questions/54758272/why-is-the-downcast-in-crtp-defined-behaviour
// https://www.codenong.com/54758272/
void test_static_cast() {
  Base *b = getObject(true);

  if (b->getClassID() == DERIVED) {
    // We already proved b is pointing to a Derived object, so this should
    // always succeed
    Derived1 *d = static_cast<Derived1 *>(b);
    std::cout << "The name of the Derived is: " << d->getName() << '\n';
  }

  delete b;
}
void test_test_dynamic_cast() { Derived1 }
int main() {
  test_static_cast();
  return 0;
}