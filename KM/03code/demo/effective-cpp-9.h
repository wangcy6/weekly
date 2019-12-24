#include "iostream"
#include <typeinfo>
using namespace std;

class Person {
public:
  string &name;
  int &m_ref;
  Person(string &str, int len) : name(str), m_ref(len) {
    cout << "name=" << name << "val=" << m_ref << ":" << &m_ref << endl;
  }
};
