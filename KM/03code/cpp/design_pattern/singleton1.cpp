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


class state_deleter {  // a deleter class with state
  int count_;
public:
  state_deleter() : count_(0) {}
  template <class T>
  void operator()(T* p) {
    std::cout << "[deleted #" << ++count_ << "]\n";
    delete p;
  }
};

class SingletonBase
{
public:
    static SingletonBase *GetInstance();

private:
    static unique_ptr<SingletonBase,state_deleter> m_instance;
   
private:

    friend  unique_ptr<SingletonBase,state_deleter>::deleter_type;
    
    SingletonBase() { cout << "singletonBase" << endl; }
    ~SingletonBase() { cout << "~singletonBase" << endl; }
    SingletonBase &operator=(const SingletonBase &) {}
   
public:
    class GarbageCollector
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
            // if (SingletonBase::instance) {
            //     delete SingletonBase::instance;
            //     SingletonBase::instance = 0;
            // }
        }
    };
};

SingletonBase *SingletonBase::GetInstance()
{
    if (m_instance.get() == NULL)
    {
        // m_instance.reset(std::make_shared<SingletonBase>());
        m_instance.reset(new SingletonBase());
    }
    return m_instance.get();
    return NULL;
}

unique_ptr<SingletonBase,state_deleter> SingletonBase::m_instance;

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

//unique_ptr Singleton private-destructor
//http://www.cplusplus.com/reference/memory/unique_ptr/

//http://erdani.com/publications/DDJ_Jul_Aug_2004_revised.pdf
//http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/
//https://blog.csdn.net/linuxwuj/article/details/81187564
//http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/
//https://stackoverflow.com/questions/15193108/c-unique-ptr-versus-friend-class-private-destructor
//https://stackoverflow.com/questions/29896268/friend-function-is-unable-to-construct-a-unique-pointer-of-the-class/29897846
//#134: make_unique and private constructors
//https://social.msdn.microsoft.com/Forums/sqlserver/en-US/828b8a8f-a27a-46b6-a1b6-2372270037c0/stdmakeshared-cannot-invoke-a-private-constructor-even-if-the-constructor-is-accessible-at?forum=vcgeneral
//http://senlinzhan.github.io/2015/04/20/%E8%B0%88%E8%B0%88C-%E7%9A%84%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88/
//g++ --std=c++11 singleton.cpp