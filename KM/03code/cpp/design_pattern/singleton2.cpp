/*************************************************************************
    > File Name: Singleton 
    > Author: wangcy6 
    > Mail: wang_cyi@163.com

单例模式（Singleton Pattern) 它用来保证系统中最多只能存在一个它的实例
1. 作为一条普通的类的成员），分配堆上还是栈上？如果分配栈上自动析构，不考虑释放问题。我需要考虑new T()的问题
2. 作为一条普通的类，getInstance() 返回类型T* 谁来释放？ 
   --- 1. 进程退出时候atexit清理，进程不退出不释放 
   -----2 GarbageCollector

 ************************************************************************/

#include <iostream>
#include <memory>

using namespace std;

///////////////////////////Singleton.h////////////////////////
class SingletonBase
{
public:
    static SingletonBase *GetInstance(); //对外接口

private:
    class GarbageCollector // 清理数据
    {
    public:
        void operator()(SingletonBase *ptr) const
        {
            if (ptr)
            {
                delete ptr;
            }
        }
        ~GarbageCollector()
        {
            cout << " ~GarbageCollector" << endl;
        }
    };
    class GarbageCreate // 全局静态变量
    {  
      public:
        GarbageCreate()
        {    
            cout<<" safe create before main()"<<endl;
            SingletonBase::GetInstance(); //在main函数之前执行
        }
    };

    
    friend unique_ptr<SingletonBase, SingletonBase::GarbageCollector>::deleter_type;
   

    SingletonBase() { cout << "singletonBase" << endl; }
    ~SingletonBase() { cout << "~singletonBase" << endl; }
    SingletonBase &operator=(const SingletonBase &) {}

private:
    static unique_ptr<SingletonBase, SingletonBase::GarbageCollector> m_instance;
    static GarbageCreate m_mainBefore; //
};

///////////////////////////Singleton.cpp////////////////////////
SingletonBase::GarbageCreate SingletonBase::m_mainBefore;//创建单例
unique_ptr<SingletonBase, SingletonBase::GarbageCollector> SingletonBase::m_instance; //静态变量构造

SingletonBase *SingletonBase::GetInstance()
{
    if (m_instance.get() == NULL)
    {
        //m_instance.reset(std::make_unique<SingletonBase>());
        m_instance.reset(new SingletonBase());
    }
    return m_instance.get();
}

int main()
{

    if (SingletonBase::GetInstance() == SingletonBase::GetInstance())
    {
        cout << "I am only one  " << endl;
    }
    else
    {
        cout << "I am many instances " << endl;
    }
}
//https://stackoverflow.com/questions/48780550/why-make-unique-fails-with-private-constructor
//https://en.cppreference.com/w/cpp/language/pimpl
//https://stackoverflow.com/questions/24095071/incomplete-type-in-nested-name-specifiers