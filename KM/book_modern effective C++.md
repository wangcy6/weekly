# 一定看英文的Effective_Modern_C++（包含c++11）



## Item 12: Declare overriding functions override 



翻译：https://www.cnblogs.com/boydfd/p/5018235.html

- 虚函数作用

virtual function implementations in derived classes override the implementa-
31 tions of their base class counterparts 

虚函数 重写了基类的实现，我们叫它覆盖，不是重载要，看到这2个名词脑瓜疼



It’s disheartening, then, to realize how easily  virtual function overriding can go wrong 

哪里危险了

为了能够成功重写，必须要符合一些要求：

- 基类函数必须是virtual的。
- 基类函数和派生类函数的名字必须完全一样（除了析构函数）。
- 基类函数和派生类函数的参数类型必须完全一样。
- 基类函数和派生类函数的const属性必须完全一样。
- 基类函数和派生类函数的返回值类型以及异常规格（exception specification）必须是可兼容的。

~~~c++
class Base {
public:
    virtual void doWork();          //基类虚函数
    ...
};

class Derived: public Base{
public:
    virtual void doWork();          //重写Base::doWork
    ...                             //（“virtual” 是可选的）
};

std::unique_ptr<Base> upb =         //创建基类指针，来指向
    std::make_unique<Derived>();    //派生类对象;有关
                                    //std::make_unique的信息
                                    //请看Item 21
...

upb->doWork();                      //通过基类指针调用doWork;
                                    //派生类的函数被调用了
~~~



- why ，c++11 都特此声明了

  ~~~c++
  struct A
  {
      virtual void foo();
      void bar();
  };
   
  struct B : A
  {
      void foo() const override; // 错误：B::foo 不覆盖 A::foo
                                 // （签名不匹配）
      void foo() override; // OK：B::foo 覆盖 A::foo
      void bar() override; // 错误：A::bar 非虚
  };
  override 指定一个虚函数覆盖另一个虚函数。
  https://zh.cppreference.com/w/cpp/language/override
  http://www.voidcn.com/article/p-kahimdvj-xh.html
  
  ~~~

  

  - What is name hiding in C++?

  ~~~c++
#include <iostream>
  #include <string>
using namespace std;
  
  class Base {
  public:
    virtual int f() const { 
      cout << "Base::f()\n"; 
      return 1; 
    }
    virtual void f(string) const {}
    virtual void g() const {}
  };
  
  class Derived1 : public Base {
  public:
    void g() const {}
  };
  
  class Derived2 : public Base {
  public:
    // Overriding a virtual function:
    int f() const { 
      cout << "Derived2::f()\n"; 
      return 2;
    }
  };
  
  class Derived3 : public Base {
  public:
    // Cannot change return type:
    //! void f() const{ cout << "Derived3::f()\n";}
  };
  
  class Derived4 : public Base {
  public:
    // Change argument list:
    int f(int) const { 
      cout << "Derived4::f()\n"; 
      return 4; 
    }
  };
  
  int main() {
    string s("hello");
    Derived1 d1;
    int x = d1.f();
    d1.f(s);
    Derived2 d2;
    x = d2.f();
  //!  d2.f(s); // string version hidden
    //子类重载一个基类的函数，基类其他版本 虽然继承了，但是看不到
    Derived4 d4;
    x = d4.f(1);
  //!  x = d4.f(); // f() version hidden
  //!  d4.f(s); // string version hidden
    Base& br = d4; // Upcast
  //!  br.f(1); // Derived version unavailable
    br.f(); // Base version available
    br.f(s); // Base version abailable
  } ///:~
  ~~~
  
  
  
  ## 智能指针
  
  ### Item 20: Use std::unique_ptr for exclusive-ownership re-source management. 



# c++11 新特性

### [c++11特性之override和final关键字](https://www.kancloud.cn/wangshubo1989/new-characteristics/99708)

override确保在派生类中声明的重载函数跟基类的虚函数有相同的签名