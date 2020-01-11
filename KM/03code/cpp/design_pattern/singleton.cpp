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


class SingletonBase
{

public:
    static int *m_main_before;
    static SingletonBase* GetInstance();
private:
    static auto_ptr<SingletonBase> m_instance;

private:
    friend class auto_ptr<SingletonBase>;
    SingletonBase() { cout << "singletonBase" << endl; }
     ~SingletonBase() { cout << "~singletonBase "  << m_main_before<< endl; }
    SingletonBase &operator=(const SingletonBase &) {}

};
SingletonBase *SingletonBase::GetInstance()
{  
    if (m_instance.get() ==NULL)
    { 
       // m_instance.reset(std::make_shared<SingletonBase>());
        m_instance.reset(new SingletonBase());
    }
    return  m_instance.get();
}
auto_ptr<SingletonBase> SingletonBase::m_instance ;

int* SingletonBase::m_main_before =new int(3) ;

int main()
{   
    
    if (SingletonBase::GetInstance() == SingletonBase::GetInstance())
    {
        cout<< "I am only one  "<<endl;
    }else
    {
       cout<< "I am many instances "<<endl;
    }
    
}


//https://www.jianshu.com/p/77c2988be336
//http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/
//https://songlee24.github.io/2014/03/11/singleton-pattern/
//https://blog.csdn.net/linuxwuj/article/details/81187564
//https://blog.csdn.net/jfkidear/article/details/53022994
//http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/
//https://stackoverflow.com/questions/15193108/c-unique-ptr-versus-friend-class-private-destructor
//https://stackoverflow.com/questions/29896268/friend-function-is-unable-to-construct-a-unique-pointer-of-the-class/29897846
//#134: make_unique and private constructors
//https://social.msdn.microsoft.com/Forums/sqlserver/en-US/828b8a8f-a27a-46b6-a1b6-2372270037c0/stdmakeshared-cannot-invoke-a-private-constructor-even-if-the-constructor-is-accessible-at?forum=vcgeneral
//http://senlinzhan.github.io/2015/04/20/%E8%B0%88%E8%B0%88C-%E7%9A%84%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88/
//g++ --std=c++11 singleton.cpp 
//https://stackoverflow.com/questions/137975/what-is-so-bad-about-singletons