#include <memory>
#include <iostream>
 
struct Foo {
    Foo(int n = 0) noexcept : bar(n) {
        //std::cout << "Foo: constructor, bar = " << bar << '\n';
    }
    ~Foo() {
         std::cout << "Foo: destructor, bar = " << bar << '\n';
    }
    int getBar() const noexcept { return bar; }
private:
    int bar;
};
 
int main()
{
    std::shared_ptr<Foo> sptr = std::make_shared<Foo>(1);
    std::cout << "The first Foo's bar is A " << sptr->getBar() << "sptr.use_count() ="<<sptr.use_count() << "\n";
 
    // 重置，交与新的 Foo 实例
    // （此调用后将销毁旧实例）
    std::shared_ptr<Foo> resetprt(sptr); 

    std::cout << "The first Foo's bar is B " << sptr->getBar() << "sptr.use_count() ="<<sptr.use_count() << "\n";
    resetprt.reset(new Foo);
    std::cout << "The first Foo's bar is C " << sptr->getBar() << "sptr.use_count() ="<<sptr.use_count() << "\n";

    sptr.reset();
    // sptr.reset();   sptr->getBar()  Segmentation fault (core dumped)
    if(sptr)
    {
        std::cout << "The second Foo's bar is " << sptr->getBar() <<sptr.use_count() <<  "\n";
    }
    
}