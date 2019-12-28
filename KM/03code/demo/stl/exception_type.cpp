#include <iostream>
#include <exception>
using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;


#define MAX_LEN 1024*1024*10 //10M
int main () {
 try
  {
    int* ptr= new int[MAX_LEN]; 
    //ok  我写代码时候没有考虑 释放虚拟内存，是否物理内存，是否产生映射，这些东西不要在说了。不然你怎么判断
    //有没有申请成功. ptr就是我的全部。
    int big[MAX_LEN];// error Segmentation Fault
  }
  catch (std::bad_alloc& ba)
  {
    std::cerr << "bad_alloc caught: " << ba.what() << '\n';
  }
  catch(std::exception& e)
  {
    //其他的错误
    cout << "other"<<e.what() << '\n';
  }

  try
  {
    throw myex;
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }
  return 0;
}

/**
 * class exception {
public:
  exception () throw();
  exception (const exception&) throw();
  exception& operator= (const exception&) throw();
  virtual ~exception() throw();
  virtual const char* what() const throw();
}
 */ 

/** 
 * 进程退出后，整个内存空间都会释放。所以不用做任何处理。
 * https://segmentfault.com/q/1010000013625384/a-1020000013779087
 * https://www.cnblogs.com/xiaowenhu/p/3542535.html
 **/ 