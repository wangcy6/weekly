#include "CThread.h" // Preferred location.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

CThread::CThread() { /*
     对象构造要做到线程安全，唯一的要求是在构造期间不要泄漏this指针，即：

     不要在构造函数中注册任何回调。
     不要在构造函数中把this指针传给跨线程的对象。
     即使是构造函数最后一行也不行（如果该类是一个基类，基类会先于派生类构造，
     执行完父类构造函数的最后一句后会接着执行子类的构造函数，
     这时most-derived class的对象还处于构造中，仍然不安全）。**/
}

CThread::~CThread() { wait(); }
int CThread::Print() {
  for (int i = 0; i < 10; ++i) {
    sleep(1);
    printf("aaaaaaaaaa-----\n");
  }
  return 0;
}
int CThread::start() {
  pthread_create(&m_tid, NULL, threadFunc, (void *)this);
  // pthread_create(&m_tid, NULL, threadFunc2, NULL);
  /***
   *    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine) (void *), void *arg);
        一般函数的指针保存函数的地址，
        而成员函数的指针和this指针共同保存出成员函数的地址，因此不能互相转换。所以成员函数不能作为pthread_create的参数。
        struct X {
        void f(int){ };
        int a;
        };
        void (X::* pmf)(int); //一个类成员函数指针变量pmf的定义
        pmf = &X::f;            //类成员函数指针变量pmf被赋值

        X ins, *p;
        p=&ins;
        (ins.*pmf)(101);       //对实例ins，调用成员函数指针变量pmf所指的函数
        (p->*pmf)(102);      //对p所指的实例，调用成员函数指针变量pmf所指的函数
   ***/
  return 0;
}
int CThread::wait() {
  if (m_tid) {
    pthread_join(m_tid, NULL);
    m_tid = 0;
    /**
     * The pthread_join() function waits for the thread specified by thread
       to terminate.  If that thread has already terminated, then
       pthread_join() returns immediately.  The thread specified by thread
       must be joinable.
     **/
    return 1;
  }
  return 0;
}