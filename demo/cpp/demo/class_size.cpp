#include <string>
#include <iostream>

using namespace std;
class A
{
public:
    virtual ~A() {}
};
class B
{
public:
    virtual ~B() {}
};

class C : public A,public B
{
public:
    virtual void test() {}
    virtual ~C() {}
};//类c不断单独产生虚表，是继承而来


class D : public  B
{
public:
    
    virtual ~D() {}
};

int main()
{   

    int* ptr;
    C* ptrc= new C();
    B* pd= new D();

    cout << "##sizeof(ptr)=" << sizeof(ptr) << endl;
    cout << "##sizeof(A)=" << sizeof(A) << endl;//8
    cout << "##sizeof(B)=" << sizeof(B) << endl;//8
    cout << "##sizeof(G)=" << sizeof(C) << endl; //16
    cout << "##sizeof(D)=" << sizeof(D) << endl; //16
    return 0;
}
//https://www.voorp.com/a/C%E5%A4%9A%E6%80%81%E5%A4%9A%E9%87%8D%E7%BB%A7%E6%89%BF%E4%B8%8E%E8%99%9A%E7%BB%A7%E6%89%BF%E7%BB%93%E5%90%88%E6%97%B6%E5%AF%B9%E5%86%85%E5%AD%98%E5%B8%83%E5%B1%80sizeof%E7%9A%84%E5%BD%B1CSDN%E5%8D%9A%E5%AE%A2