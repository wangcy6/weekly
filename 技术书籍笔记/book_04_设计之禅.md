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

- JDK源码

  



## 代码



https://github.com/fifilyu/the-23-gang-of-four-design-patterns-with-cplusplus

https://github.com/micooz/DesignPattern

https://github.com/TechieLiang/CppDesignPattern

# 目录

## 第一个 单例

[实现Singleton模式(单例模式)](https://github.com/luofengmacheng/algorithms/blob/master/interviewOffer/2.md)

[不能被继承的类](https://github.com/luofengmacheng/algorithms/blob/master/interviewOffer/48.md)



vitura l base class 会在mosted derived class 中先被调用，

然后在处于中间层的base class中抑制vitural base class的constructor，

以保证virtual base class共享一份。

如果少了virtual继承则是递归的调用constructor，就不能实现final的功能啦



https://blog.gocalf.com/cpp-singleton

https://www.cnblogs.com/faith0217/articles/4083484.html

https://www.jianshu.com/p/333d4b37db56



### 1.4 代码

	### 单例

~~~c++
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
~~~



## 第二个 工厂（三个 简单，方法，抽象）

### 2.1 意图

- 对 客户提供一个接口，然后直接使用。不关系具体实现。

  画外音

  > 这就是多态呀
  >
  > 不同子对象都有相同的抽象基类  
  >
  > 声明一个指向基类的指针来指向实际的子 类实现。
  >
  > 例如：客户端想链接数据库，具体什么数据怎么链接，客户不关系，你们帮我处理好就可以了。只要能连结就可以。

- 而无需指定它们具体的类  ，具体化类的工作延迟到了子类中

  

  画外音：

  > 在父类中并不知道具体要实例化哪一个具体的子类  
  >
  > 让子类决定实例化哪一个类  。
  >
  > 那么问题来了 如何知道具体类呢？
  >
  > 例如 不同类型的汽车，不同类型的装修。不同口味的食物，游戏中不同等级怪物



### 2.2   问题

- Factory 模式  是什么？

  > if 不知道是什么， then 不要去想对应缺点

  

- 有什么缺点

~~~c++
class Factory {
public:
    virtual ~Creator() { };
    virtual Product *Create() = 0; 
    //1 Product 是base ，所有的产品将返回类型所给定的相同的抽象接口返回给客户。
    //客户将不能区分或对一个产品的类别进行安全的假定
    //2 因为没有参数，我也不知道创建什么
};
class AbstractFactory {
public:
  virtual ~AbstractFactory();
  virtual AbstractProductA* CreateProductA() = 0; //
  virtual AbstractProductB* CreateProductB() = 0;// 如果创建C,D呢?
};

~~~



### 2.3 别人怎么解决



阅读 https://www.jianshu.com/p/b2a06667b63a   10分钟 3个方式

阅读  https://www.jianshu.com/p/1a74c6ad1b58 10分钟

https://www.jianshu.com/p/5efb80654a1c

#### to_do  正在消化

~~~
工厂模式
创建对象而不将实例化逻辑暴露给客户端，并通过公共接口引用新创建的对象。
例如：

java.lang.Object#toString() (在所有子类中重写)
java.lang.Class#newInstance()
java.lang.Integer#valueOf(String)
java.lang.Class#forName()
java.lang.reflect.Array#newInstance()
java.lang.reflect.Constructor#newInstance()

抽象工厂
提供用于创建一系列相关对象的接口，而无需显式指定其类。 我们可以简单地说它是工厂模式的更高层次的抽象
例如：

java.util.Calendar#getInstance()
java.util.Arrays#asList()
java.util.ResourceBundle#getBundle()
java.net.URL#openConnection()
java.sql.DriverManager#getConnection()
java.sql.Connection#createStatement()
java.sql.Statement#executeQuery()
java.text.NumberFormat#getInstance()
java.lang.management.ManagementFactory (所有getXXX（）方法)
java.nio.charset.Charset#forName()
javax.xml.parsers.DocumentBuilderFactory#newInstance()
javax.xml.transform.TransformerFactory#newInstance()
javax.xml.xpath.XPathFactory#newInstance()

作者：惜时如金
链接：https://juejin.im/post/5cbfdb406fb9a0322c428f2c
来源：掘金
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
~~~



#### 方法1 使用模板以避免创建子类  

demo  C++ 

- 无继承的vector怎么知道的？

~~~c++
std::vector<int>
std::vector<string>
std::vector<std:vector<int>>;

network *net = factory_store<network>::create(xxx);
~~~

- 有继承的怎么做的?

  ~~~c++
  class CUser:public SingletonBase<CUser>
  {
      // 还是模板T
  }
  
  ~~~

  

#### 	  方法2  传递参数（固定不会发送变化）



### 2.4 code



## 第三个 观察者

#### 3.1 意图

当一个对象的状态发生改变时 , 所有依赖于它的对象 都得到通知并被自动更新 。



#### 3.2   问题

- 什么是

![](https://upload-images.jianshu.io/upload_images/93313-b9993038ce689b58.png?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)

#### 3.3 别人怎么解决

#### 3.4 code

### 扩展

https://github.com/luofengmacheng/algorithms



第三个 Bridge 模式  