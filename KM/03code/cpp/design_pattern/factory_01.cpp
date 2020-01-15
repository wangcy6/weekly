#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

//定义基类
class Base
{
public:
    //析构函数为虚函数
    virtual ~Base()
    {
    }
};

class Derived : public Base
{
public:
    void printf()
    {
        cout << "I'm a Derived." << endl;
    }
};

void test(Base* b)
{
    const type_info& tb = typeid(*b);
    
    //tb为type_info类，使用name成员函数可以得到类型名称
    cout << tb.name() << endl;
}

int main(int argc, char *argv[])
{
    int i = 0;
    
    //这里使用typeid来获取类型
    const type_info& tiv = typeid(i);
    const type_info& tii = typeid(int);
    
    cout << (tiv == tii) << endl;
    
    Base b;
    Derived d;
    
    test(&b);
    test(&d);
    
    return 0;
}
//https://stackoverflow.com/questions/2354210/can-a-class-member-function-template-be-virtual
//https://www.zhihu.com/question/38043914