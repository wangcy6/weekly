#include <iostream>
using  namespace std;
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
	//error: ‘void B::bar()’ marked ‘override’, but does not override
};

//g++ -std=c++11   class_function.cpp 
int main(void) {
    
    
    return 0;
}