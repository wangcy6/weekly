#include <iostream>
using namespace std;

class Grandparent {
 public:
  virtual void grandparent_foo() {}
  int grandparent_data;
};

class Parent1 : virtual public Grandparent {
 public:
  virtual void parent1_foo() {}
  int parent1_data;
};

class Parent2 : virtual public Grandparent {
 public:
  virtual void parent2_foo() {}
  int parent2_data;
};

class Child : public Parent1, public Parent2 {
 public:
  virtual void child_foo() {}
  int child_data;
};

int main() {
  Child child;
}

/**
https://blog.csdn.net/anzhsoft/article/details/18600163
https://shaharmike.com/cpp/vtable-part3/
https://zhuanlan.zhihu.com/p/61585620

set p obj on
set p pretty on
$2 = {
  <Parent1> = {
    <Grandparent> = <invalid address>, 
    members of Parent1: 
    _vptr.Parent1 = 0x0, 
    parent1_data = 0
  }, 
  <Parent2> = {
    members of Parent2: 
    _vptr.Parent2 = 0x400970 <__libc_csu_init>, 
    parent2_data = 4196048
  }, 
  members of Child: 
  child_data = 0
}
**/