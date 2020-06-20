#include <thread>
#include <atomic>
#include <cassert>
#include <string>
 
std::atomic<std::string*> ptr;
int data;
 
void producer()
{
    std::string* p  = new std::string("Hello");
    data = 42;
    // 这句要放在最后，目的是为了在consumer中看到data的副带效应
    ptr.store(p, std::memory_order_release);
}
 
void consumer()
{
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_acquire))) {
        ;
    }
    // 下面的两个断言永远为真
    assert(*p2 == "Hello");
    // producer中执行store之前的操作，在这里也可以看到
    assert(data == 42);
}
 
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}
