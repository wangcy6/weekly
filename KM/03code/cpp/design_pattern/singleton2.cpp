/*************************************************************************
    > File Name: Singleton 
    > Author: wangcy6 

单例模式（Singleton Pattern) 它用来保证系统中最多只能存在一个它的实例
1. 作为一条普通的类的成员），分配堆上还是栈上？--如果分配栈上自动析构，不考虑释放问题。我需要考虑new T()的问题。
2. 作为一条普通的类，getInstance() 返回类型T* 谁来释放？ 
   --- 1. 进程退出时候atexit清理，进程不退出不释放 
   -----2 GarbageCollector
3.  线程安全
    
   1 编译时候s
     static变量，全局/静态存储区  
     在进入main函数之前应该是单线程的 ，不需要使用锁机制

   2 延迟初始化 
     存在线程安全问题 引入lock 。
4. 改为为 T 模板 [没有实现]
5 一个不能被继承的单例类 [没有实现]



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
    class GarbageCollector //内部类- 清理数据
    {
    public:
        void operator()(SingletonBase *ptr) const //函数对象
        {
            if (ptr)
            {
                delete ptr;
            }
        }
        ~GarbageCollector()
        {
            cout << " after after main  ~GarbageCollector " << endl;
        }
    };
    class GarbageCreate //内部类-创建数据
    {
    public:
        GarbageCreate() //构造函数
        {
            cout << " safe create before main()" << endl;
            SingletonBase::GetInstance(); //在main函数之前执行，不存在线程竞争问题
        }
    };

    friend unique_ptr<SingletonBase, SingletonBase::GarbageCollector>::deleter_type; // 自定义析构

    SingletonBase() { cout << "singletonBase" << endl; }
    ~SingletonBase() { cout << "~singletonBase" << endl; }
    SingletonBase &operator=(const SingletonBase &) {}

private:
    static unique_ptr<SingletonBase, SingletonBase::GarbageCollector> m_instance; //销毁
    static GarbageCreate m_mainBefore; // 创建 
};

///////////////////////////Singleton.cpp////////////////////////
unique_ptr<SingletonBase, SingletonBase::GarbageCollector> SingletonBase::m_instance; //静态变量初始化 内部类之间调用private函数
SingletonBase::GarbageCreate SingletonBase::m_mainBefore;                             //创建单例 内部类之间调用private函数


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

//遇到的语法问题
//https://stackoverflow.com/questions/317450/why-override-operator
//https://stackoverflow.com/questions/48780550/why-make-unique-fails-with-private-constructor
//https://en.cppreference.com/w/cpp/language/pimpl
//https://stackoverflow.com/questions/24095071/incomplete-type-in-nested-name-specifiers