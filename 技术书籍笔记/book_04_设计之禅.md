---
title: "设计之禅"
date: 2019-11-27
description: ""
draft: false
tags: ["book","大话设计模式"]
categories: ["大话设计模式"]
---

# 书籍

- [设计模式：可复用面向对象软件的基础](https://zh.wikipedia.org/wiki/设计模式：可复用面向对象软件的基础)

- 领域驱动设计

- 重构--改善既有代码的设计

- 设计模式精解－GoF 23 种设计模式解析附 C++实现源码

  



## 代码



https://github.com/fifilyu/the-23-gang-of-four-design-patterns-with-cplusplus

https://github.com/micooz/DesignPattern

https://github.com/TechieLiang/CppDesignPattern

# 目录

### 单例

[实现Singleton模式(单例模式)](https://github.com/luofengmacheng/algorithms/blob/master/interviewOffer/2.md)

[不能被继承的类](https://github.com/luofengmacheng/algorithms/blob/master/interviewOffer/48.md)

https://blog.gocalf.com/cpp-singleton







# 代码

	### 单例

~~~c++
/*************************************************************************
    > File Name: Singleton 
    > Author: wangcy6 
    > Mail: wang_cyi@163.com

单例模式（Singleton Pattern) 它用来保证系统中最多只能存在一个它的实例
1. 作为一条普通的类的成员），分配堆上还是栈上？如果分配栈上自动析构，不考虑释放问题。我需要考虑new T()的问题
2. 作为一条普通的类，getInstance() 返回类型T* 谁来释放？ 
   --- 1. 进程退出时候atexit清理，进程不退出不释放 
   -----2 GarbageCollector
3.  线程安全
    
   1 编译时候s
     static变量，全局/静态存储区  
     在进入main函数之前应该是单线程的 ，不需要使用锁机制

   2 延迟初始化 
     存在线程安全问题 引入lock 。
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


    friend unique_ptr<SingletonBase, SingletonBase::GarbageCollector>::deleter_type; // 自定义析构
   

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
~~~





### 扩展

https://github.com/luofengmacheng/algorithms