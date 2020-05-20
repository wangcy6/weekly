 
#include<iostream>  
using namespace std;  

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
class Base  
{  
public:  
    virtual void f(float x)  
    {  
        cout<<"Base::f(float)"<< x <<endl;  
    }  
    void g(float x)  
    {  
        cout<<"Base::g(float)"<< x <<endl;  
    }  
    void h(float x)  
    {  
        cout<<"Base::h(float)"<< x <<endl;  
    }  
};  
class Derived : public Base  
{  
public:  
    virtual void f(float x)  
    {  
        cout<<"Derived::f(float)"<< x <<endl;   //多态、覆盖  
    }  
    void g(int x)  
    {  
        cout<<"Derived::g(int)"<< x <<endl;     //隐藏  
    }  
    void h(float x)  
    {  
        cout<<"Derived::h(float)"<< x <<endl;   //隐藏  
    }  
};  
int main(void)  
{  
    Derived d; 
	
    Base *pb = &d;  
    Derived *pd = &d;  

    // Good : behavior depends solely on type of the object  
    pb->f(3.14f);   // Derived::f(float) 3.14  
    pd->f(3.14f);   // Derived::f(float) 3.14  
  
    // Bad : behavior depends on type of the pointer  
    pb->g(3.14f);   // Base::g(float)  3.14  
    pd->g(3.14f);   // Derived::g(int) 3   
  
    // Bad : behavior depends on type of the pointer  
    pb->h(3.14f);   // Base::h(float) 3.14  
	
	
    pd->h(3.14f);   // Derived::h(float) 3.14  
    return 0;  
}  