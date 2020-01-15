/*************************************************************************
    > File Name: Observer 
    > Author: wangcy6 
    > Mail: wang_cyi@163.com
   观察者模式（Observer Pattern) 
1. 如何写一个线程安全的目标类(Subject)?

     不好意思，我现在根本不知道哪里有危险，race conditions 用锁解决自己内部冲突，
     我就是不知道呀？我怎么回答

     Using weak_ptr to implement the Observer pattern  race conditions 

2. 
 ************************************************************************/
#include <iostream>

#include <vector>

using namespace std;
/////////////////////////Observer.h///////////////////////////
class Subject;
class Observer
{
public:
    virtual ~Observer();
    virtual void update() = 0;

protected:
    Subject *m_subject;
};

/////////////////////////Subject.h///////////////////////////
class Observer;
//目标
class Subject
{
public:
    virtual ~Subject();
    virtual void Subscribe(weak_ptr<Observer> observer);
    //virtual void Detach(weak_ptr<Observer> observer);
    virtual void notifyObservers();

private:
    std::vector<weak_ptr<Observer>> m_observerslist;
    //  std::vector<share_ptr<Observer>> m_observerslist; 这样有什么后果呢？
    //多个 shared_ptr 对象可占有同一对象，资源永源不会释放。
    typedef std::vector<weak_ptr<Observer>>::iterator Iterator;
};

/////////////////////////Observer.cpp///////////////////////////

/////////////////////////Subject.cpp///////////////////////////

void Subject::notifyObservers()
{
    Iterator it = m_observerslist.begin();
    while (it != m_observerslist.end())
    {
        shared_ptr<Observer> obj(it->lock());
        cout<<"use_count="<<objuse_count()<<endl;
        if (obj)
        {
            obj->update();
            ++it;
        }
        else
        {
            it = m_observerslist.erase(it);
        }
    }
}
void Subject::Subscribe(weak_ptr<Observer> observer)
{
    observers_.push_back(observer);
}
//https://stackoverflow.com/questions/53727439/registering-weak-ptr-observer-in-constructor
//http://blog.leanote.com/post/976983457@qq.com/%E8%A7%82%E5%AF%9F%E8%80%85%E7%9B%91%E5%90%AC%E8%80%85%E6%A8%A1%E5%BC%8F