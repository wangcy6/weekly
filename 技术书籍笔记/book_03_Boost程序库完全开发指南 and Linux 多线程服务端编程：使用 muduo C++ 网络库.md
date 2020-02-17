

## 配合一切阅读

https://github.com/chenshuo/documents

Linux 多线程服务端编程：使用 muduo C++ 网络库

![](../images/cover.jpg)

# 准备工作

Ubuntu 安装boost 库 编译

```
git clone --recursive https://github.com/boostorg/boost.git
cd boost
git checkout develop # or whatever branch you want to use
./bootstrap.sh
./b2 headers

yum install cmake3


```



代码 https://github.com/boostorg/thread

#  第一章  观察者模式与智能指针

 https://www.boost.org/doc/libs/1_61_0/libs/smart_ptr/shared_ptr.htm
  Because the implementation uses reference counting, cycles of shared_ptr instances will not be reclaimed.



~~~c++
int main()
{
  Foo* p = new Foo;
  Observable subject;
  p->observe(&subject);
  subject.notifyObservers();
  delete p;
  //subject 不知道 p已经删除了。
  subject.notifyObservers();
}
int main()
{
  Observable subject;
  {
    boost::shared_ptr<Foo> p(new Foo);
    p->observe(&subject);
    subject.notifyObservers();
  } 
  //没有通知subject p已经消失
  subject.notifyObservers();
}

 element_type * px;                 // contained pointer
 boost::detail::shared_count pn;    // reference counter

sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int use_count_;        // #shared
    int weak_count_;       // #weak + (#shared != 0)

~~~





# 内存管理 76page



![image.png](../images/XpBAW8L61kOdZwz.png)

![image-20200103152815380](../images/image-20200103152815380.png)



![image-20200103155245043](../images/image-20200103155245043.png)

![image-20200103155348842](../images/image-20200103155348842.png)

![image-20200103160638457](../images/image-20200103160638457.png)

- 我在这里

https://github.com/wangcy6/weekly/blob/master/KM/03code/cpp/smart_ptr-develop/include/boost/smart_ptr/shared_ptr.hpp





https://github.com/wangcy6/weekly/blob/master/KM/03code/cpp/smart_ptr-develop/include/boost/smart_ptr/detail/shared_count.hpp



# 第三部分 线程模块

3.1 共享互斥 `shared_mutex`

> book 497page 

 Boost 都提供了 `shared_mutex` 来解决「读者-写者」问题。多个读线程 一个写线程。

shared_mutex` 这个名字并不十分贴切，不如 pthread 直呼「读写锁」





# 第四部分 Boost与设计模式



- 单例 https://www.jianshu.com/p/333d4b37db56

阅读：程序员的自我修养—链接、装载与库 第10章 11章 311page 338page 

# References

[1]  https://zh.cppreference.com/w/cpp/thread/shared_mutex

[2] https://zh.cppreference.com/w/cpp/thread/condition_variable

