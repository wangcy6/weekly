#include <iostream>
using namespace std;

class Top1
{
public:
  int a;
  virtual  ~Top1() {}
};

class Left1 :  public Top1
{
public:
  int b;

};

class Top
{
public:
  int a;
  //~Top() {} fuck virtual 忘记声明了，你以为~就是虚函数了
 virtual  ~Top() {}
};

class Left : virtual public Top
{
public:
  int b;

};

class Right : virtual public Top
{
public:
  int c;
};

class Bottom : public Left, public Right
{
public:
  int d;
};

class AnotherBottom : public Left, public Right
{
public:
  int d;
};

void test1()
{
  Left1 l1;
  Top1 t1;
  
  Bottom *bottom1 = new Bottom();
  AnotherBottom *bottom2 = new AnotherBottom();

  Top *top1 = bottom1;
  Top *top2 = bottom2;
  
  //Left *left = static_cast<Left*>(top1);  //static_cast  不适用 A 和B 之间继承有歧义，可能存在多个 无法跳转的

  //Bottom *sbp = static_cast<Bottom*>(top1); 
  Bottom *sbp = dynamic_cast<Bottom*>(top1);  //static_cast  不适用虚继承的down转换
  
  //error: cannot convert from base ‘Top’ to derived type ‘Left’ via virtual base ‘Top’
  //注意这里我们并不清楚对于top1指针指向的对象是Bottom还是AnotherBottom。
  //这里是根本不能编译通过的！因为根本不能确认top1运行时需要调整的偏移量(对于Bottom是20，对于AnotherBottom是24)
}

void testSize()
{  
  Top t;
  Left left;
  Right r;
  Bottom b;
  cout<< "sizeof(int)= " <<sizeof(int)<<endl; //
  cout<< "sizeof(int*)= " <<sizeof(int*)<<endl; //
  cout<< "sizeof(Top)= " <<sizeof(Top)<<endl; //8
  cout<< "sizeof(Left)= " <<sizeof(Left)<<endl;//12
  cout<< "sizeof(Right)= " <<sizeof(Right)<<endl;//12
  cout<< "sizeof(Bottom)= " <<sizeof(b)<<endl;//20

// sizeof(int)= 4
// sizeof(int*)= 8
// sizeof(Top)= 16
// sizeof(Left)= 32
// sizeof(Right)= 32
// sizeof(Bottom)= 48
}
int main()
{
  test1();
  testSize();
  return 0;
}

//https://www.cnblogs.com/dirichlet/archive/2010/04/01/2542360.html
//https://coolshell.cn/articles/12176.html

//浅拷贝,引用计数copy，移动copy  深度拷贝。
