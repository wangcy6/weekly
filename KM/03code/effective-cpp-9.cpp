#include "effective-cpp-9.h"
#include "iostream"
#include <typeinfo>
using namespace std;

int main() {

  string s1 = "alice", s2 = "bob";
  Person p1(s1, 1), p2(s2, 10);

  //p1 = p2;

  Person p3(p1);
  cout << p3.name << ":" << &p2.m_ref;
 
  return 0;
}

/**
https://en.cppreference.com/w/cpp/language/copy_assignment
error: non-static reference member ‘std::string& Person::name’, can’t use default assig
 ment operator

Assignment operator (C++) In the C++ programming language, the assignment
operator =, Copy assignment operator A copy assignment operator of class T is a
non-template non-static member function with the name operator= that takes
exactly one parameter of type T, T&, const T&, volatile T&, or const volatile
T&.

**/