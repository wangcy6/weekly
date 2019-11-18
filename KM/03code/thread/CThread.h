// CThread.h
#include <pthread.h>
class CThread {
public:
  CThread();
  ~CThread();
  virtual int Print();
  int start(); //线程启动
  //静态函数。使用类中的成员
  static void *threadFunc(void *arg) {
    CThread *obj = static_cast<CThread *>(arg);
    obj->Print();
    return NULL;
  }

private:
  pthread_t m_tid;

private:
  int wait(); //封装在析构函数里面，不让外围使用。
};