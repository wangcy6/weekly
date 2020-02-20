/*************************************************************************
    > File Name: Singleton 
    > Author: wangcy6 
    > wang_cyi@163.com

单例模式（Singleton Pattern) 它用来保证系统中最多只能存在一个它的实例, 如何保证

1. 该对象分配程序的内存分配那个位置， 栈区，堆区还是初始化全局区(.data) ，未初始化的全局区(.bss)吗？?
  -----分配在初始化全局区(.data)，需要调用构造函数来执行

2. 考虑如果全局区初始化失败，内存不够情况吗？
  ---全局区存储是指针或者智能指针，就可以了。new 失败如何不抛出异常  new (std::nothrow) 

3. 是线程安全的吗？
       --static 变量在main 函数申请，在main函数解释释放 都是单线程，100%安全，
        放到main只能无法保证了，鬼知道用户怎么使用，你无法约束。

4  基类创建时候如何知道具体实现（不能被继承）？
   ---具体成员用模板T代替，构造函数private 
      T must be: no-throw default constructible and no-throw destructible

5. 能被继承吗？这是问题4的延伸（可以被继承，这个定义不严格，可以舍去）
   ---单例模式只是一个模式，不负责具体存储具体数据类型（你存储map,还是mutex）需要子类实现 
      依然用模板T，构造函数protreted
  说明：虽然子类 可以实例化多次，但是static是全局唯一的，不多次创建（boost没有采用这个方式）
   
用法：
1
typedef SingletonBase<shared_pool_t> singleton;//不能被继承（推荐 这更严格）
singleton::instance()

2 
class CUser:public SingletonBase<CUser>;//（可以被继承，这个定义不严格，可以舍去）
CUser::instance()
 
 key
 1. 实例类型 T来确定 ，不抛异常 在main 之前构造，无法捕获
 2. 唯一 static 存在不存在判断
 3. 唯一 防止static 被copy走 外界 禁用 
 ************************************************************************/

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

///////////////////////////Singleton.h////////////////////////
template <typename T>
class SingletonBase
{
public:
    typedef T object_type;
    static object_type* GetInstance( )
    {
       static object_type only; //main线程之前初始化就是安全的,你也可以用智能指针代替、new代替
       return &only;
    } 
private:
    friend T; // 如果不允许子类继承，可以屏蔽 看问题5
    SingletonBase() { cout << "singletonBase" << endl; }  //声明public可以吗
    ~SingletonBase() { cout << "~singletonBase" << endl; } //声明public可以吗
    SingletonBase(const SingletonBase &) {} //must
    SingletonBase &operator=(const SingletonBase &) {} //must 


    class GarbageCreate //内部类-创建数据
    {
    public:
        GarbageCreate() //构造函数
        {
            cout << " safe create before main()" << endl;
            SingletonBase::GetInstance(); //在main函数之前执行，不存在线程竞争问题
        }
    };

    class GarbageCollector //内部类- 清理数据
    {
    public:
        void operator()(object_type *ptr) const //函数对象
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

  static GarbageCreate m_create;

};

///////////////////////////Singleton.cpp////////////////////////
template<typename T>
typename SingletonBase<T>::GarbageCreate SingletonBase<T>::m_create; 


//////////////////////ohter.cpp////////////////////
class CUser:public SingletonBase<CUser>
{
public:    
        CUser()
        {
            cout<< " CUser()" <<endl;
        }
        ~CUser()
        {
            cout<< "~CUser()" <<endl;
        }
private:
      vector<string> m_name;

};

int main()
{   

    if (CUser::GetInstance() == CUser::GetInstance())
    {   
        //GetInstance 继承基类的函数
        //
        cout << "I am only one  " << endl;
    }
    else
    {
        cout << "I am many instances " << endl;
    }
}
//声明和定义的区别
//https://www.nowcoder.com/questionTerminal/5b25d82adaed44059c7bb3a77ea9b508
//静态数据成员要在类外定义和初始化
//未定义的引用
//在链接为可执行文件的时候就必须要具体的实现了
//未声明的引用
https://blog.nowcoder.net/n/11260b9431fb4ddbb15b4d8c7f252eb3
//https://www.theimpossiblecode.com/blog/c11-generic-singleton-pattern/




//设计问题 
//http://www.justdojava.com/2019/08/21/Java-single-destroy-prevent/
//https://www.interviewsansar.com/singleton-class-design-with-an-example/ 错误的设计
//https://liam.page/2016/08/14/copy-control-in-Cpp/
//拷贝构造函数没有处理静态数据成员


//遇到的语法问题
//https://stackoverflow.com/questions/317450/why-override-operator
//https://stackoverflow.com/questions/48780550/why-make-unique-fails-with-private-constructor
//https://en.cppreference.com/w/cpp/language/pimpl
