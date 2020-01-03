#include <iostream>
#include <memory>

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

//https://www.boost.org/doc/libs/1_53_0/libs/smart_ptr/shared_ptr.htm
//https://zh.cppreference.com/w/cpp/memory/shared_ptr/

//https://blog.nowcoder.net/n/6099c91dcace4edcb9e39d7d615625ab
//https://www.cnblogs.com/bobojiang/p/8580015.html
//shared_ptr 原理及事故
//https://heleifz.github.io/14696398760857.html
/*******************************
 *  RCSP ( Reference Counting smart pointer)
 * 
 * auto_ptr :不是真正的智能智能 不具备引用技术功能
 * 
 * 
 * 
 * shared_ptr
 * 
 * 
 * weak_ptr
 *  打断 std::shared_ptr 所管理的对象组成的环状引用
 * 
 * 
 *****************************************/
using namespace std;


void test_int()
{
    int a = 10;
    
    shared_ptr<int> pinta = make_shared<int>(a);
    shared_ptr<int> pinta2(pinta);

    int b = 20;
    shared_ptr<int> pintb = make_shared<int>(b);

    cout << pinta.use_count() << endl;  //2
    cout << pintb.use_count() << endl; //1

    pinta2 = pintb;
    int *pa = pinta.get(); // 获取原始指针
    cout << pinta.use_count() << endl;//1
    cout << pintb.use_count() << endl;//2

}



struct Foo
{
   Foo(int in) : a(in) {}
   void print() const
   {
      std::cout << "a = " << a << '\n';
   }
   int a;
};

void test_operator()
{
    auto ptr = std::make_shared<Foo>(10);
    ptr->print();
    (*ptr).print();
}

struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // 注意：此处非虚析构函数 OK
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // 线程安全，虽然自增共享的 use_count
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}


void test_thread()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // 从 main 释放所有权
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';

    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
    /**
     *  Base::Base()
        Derived::Derived()

        Created a shared Derived (as a pointer to Base)
        p.get() = 0x1b17028, p.use_count() = 1

        Shared ownership between 3 threads and released
        ownership from main:
        p.get() = 0, p.use_count() = 0

        local pointer in a thread:
        lp.get() = 0x1b17028, lp.use_count() = 4

        local pointer in a thread:
        lp.get() = 0x1b17028, lp.use_count() = 6

        local pointer in a thread:
        lp.get() = 0x1b17028, lp.use_count() = 2

        Derived::~Derived()
        Base::~Base()
        All threads completed, the last one deleted Derived
     */
}
//std::weak_ptr<int> gw;


void test_weak()
{
    // OLD, problem with dangling pointer
    // PROBLEM: ref will point to undefined data!

    int* ptr = new int(10);
    int* ref = ptr;
    delete ptr;

    // NEW
    // SOLUTION: check expired() or lock() to determine if pointer is valid

    // empty definition
    std::shared_ptr<int> sptr;

    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset(new int);
    *sptr = 5;

    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;

    // weak1 is expired!
    if(auto tmp = weak1.lock())
        std::cout << *tmp << '\n';
    else
        std::cout << "weak1 is expired\n";

    // weak2 points to new data (5)
    if(auto tmp = weak2.lock())
        std::cout << *tmp << '\n';
    else
        std::cout << "weak2 is expired\n";
}

int test_expired () {
  std::shared_ptr<int> shared (new int(10));
  std::weak_ptr<int> weak(shared);

  std::cout << "1. weak " << (weak.expired()?"is":"is not") << " expired\n";

  shared.reset();

  std::cout << "2. weak " << (weak.expired()?"is":"is not") << " expired\n";

  return 0;
}

int test_lock () {
  std::shared_ptr<int> sp1,sp2;
  std::weak_ptr<int> wp;
                                       // sharing group:
                                       // --------------
  sp1 = std::make_shared<int> (20);    // sp1
  wp = sp1;                            // sp1, wp

  sp2 = wp.lock();                     // sp1, wp, sp2
  sp1.reset();                         //      wp, sp2

  sp1 = wp.lock();                     // sp1, wp, sp2

  std::cout << "*sp1: " << *sp1 << '\n';
  std::cout << "*sp2: " << *sp2 << '\n';

  return 0;
}

// g++ -std=c++11 -g Item_13.cpp -pthread
int main() 
{
    // test_int(); 
    // test_operator();  
    // test_thread();
    test_lock();
    test_expired();
    return 0;
}

//https://www.boost.org/doc/libs/1_53_0/libs/smart_ptr/shared_ptr.htm