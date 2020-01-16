/*************************************************************************
> File Name: Observer 
> Author: wangcy6 
> Mail: wang_cyi@163.com
观察者模式（Observer Pattern) 

Q1. 如何写一个线程安全的目标类(Subject)?
     不好意思，我现在根本不知道哪里有危险，我怎么回答?
     
    这里提示一下：
    Q1:如果你管理动态对象(new),vecotr<xx*> ,如果被删除了怎么办?你怎么发现？

    如果有race conditions用锁解冲突。别人删除时候抢占锁，然后删除。（接口x） 我获取锁来来使用数据，
    我不需要考虑别人不删除问题。只要存在都是对的。没毛病。

    Q2：假如你管理对象 删除后，不调用提供删除接口（接口x），你怎么知道ptr存在？
        为了防止用户疑问， oop 析构时候。然后去调用接口x，这样就安全了。没毛病

    Q3：问题有回来了，你用锁来控制安全吗？

         锁肯定安全，不然发明锁干什么！
    现在还是没get，我现在根本不知道哪里有危险，虽然互斥锁性能慢点，但是安全的 我就是不知道呀？我怎么回答

   后记：
   锁可以解决ptr存活问题，但是使用锁着工具，带来更多麻烦
   - 谁来加锁
   - 加锁对象处问题怎办？
   - 加多少个锁
   
   因此才出现了
     Using weak_ptr to implement the Observer pattern  
    https://zh.cppreference.com/w/cpp/memory/weak_ptr
    https://zh.cppreference.com/w/cpp/memory/share_ptr
 
   
    reference counting

Q2. shared_ptr,weak_ptr能完全杜绝race conditions ，实现线程安全吗？

A2
    是安全的，只要不同线程对同一个ptr操作，只先赋值一个shared_ptr在操作.不然需要加锁
    boost::shared_ptr<> offers a certain level of thread safety. 
    The reference count is manipulated in a thread safe manner 
    https://www.boost.org/doc/libs/1_61_0/libs/smart_ptr/shared_ptr.htm#Thread Safety

Q3 signal/slot机制有事什么

A3  
    理解部分：
    此Signal 不是linux的 signal
    我知道概念如下 std：fucntion 有关系。
    信号和槽的关系 当信号发送出去时，会调用信号相关联的槽函数
 
    
    不理解部分：
    https://www.boost.org/doc/libs/1_63_0/doc/html/signals.html 

    chenshuo\recipes\thread\SignalSlot.h
    https://stackoverflow.com/questions/14873364/how-to-use-signals-and-slots-for-observer-pattern

 ************************************************************************/
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
/////////////////////////Observer.h///////////////////////////
//观察者
class Observer
{
public:
    virtual ~Observer(){};
    virtual void update() = 0;
};

/////////////////////////Subject.h///////////////////////////
//目标
class Subject
{
public:
    virtual ~Subject(){}
    virtual void Subscribe(weak_ptr<Observer> observer);

    virtual void notifyObservers();

private:
    std::vector<weak_ptr<Observer>> m_observerslist;
    //  std::vector<share_ptr<Observer>> m_observerslist; 这样有什么后果呢？
    //多个shared_ptr 对象可占有同一对象，资源永源不会释放。
    typedef std::vector<weak_ptr<Observer>>::iterator Iterator;
};

/////////////////////////Observer.cpp///////////////////////////

class Foo : public Observer
{
public:

    virtual void update()
    {
        cout << "notifyObservers " << endl;
    }

    ~Foo()
    {
       cout << "I am leaving,~Foo()" << endl;
    }
};
/////////////////////////Subject.cpp///////////////////////////

void Subject::notifyObservers()
{
    Iterator it = m_observerslist.begin();
    while (it != m_observerslist.end())
    {
        shared_ptr<Observer> obj(it->lock()); //thread safe 
        if (obj)
        {   
            cout << "safe: use_count= " << obj.use_count() << endl;
            obj->update();
            ++it;
        }
        else
        {   
            cout << "ths Observer is killed"  << endl; // 
            it =m_observerslist.erase(it);
        }
    }
}
void Subject::Subscribe(weak_ptr<Observer> observer)
{
    m_observerslist.push_back(observer);
}
///////////test////////////////

int main()
{

    Subject sb;

    {
        shared_ptr<Foo> ob1(new Foo); 
        sb.Subscribe(ob1);
        sb.notifyObservers();
    }
    // new Foo is destructor 
    sb.notifyObservers();
}
//https://gist.github.com/audioplastic/4172757

//https://stackoverflow.com/questions/20705304/about-thread-safety-of-weak-ptr?noredirect=1&lq=1
//https://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety
//https://www.zhihu.com/question/56836057
//https://stackoverflow.com/questions/53727439/registering-weak-ptr-observer-in-constructor
//http://blog.leanote.com/post/976983457@qq.com/%E8%A7%82%E5%AF%9F%E8%80%85%E7%9B%91%E5%90%AC%E8%80%85%E6%A8%A1%E5%BC%8F