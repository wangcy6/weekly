#include <iostream>
 
struct V {
    virtual void f() {};  // 必须为多态以使用运行时检查的 dynamic_cast
};
struct A : virtual V {};
struct B : virtual V {
  B(V* v, A* a) {
    // 构造中转型（见后述 D 的构造函数中的调用）
    dynamic_cast<B*>(v); // 良好定义：v 有类型 V*，B 的 V 基类，产生 B*
    dynamic_cast<B*>(a); // 未定义行为：a 有类型 A*，A 非 B 的基类
  }
};
struct D : A, B {
    D() : B((A*)this, this) { }
};
 
struct Base {
    virtual ~Base() {}
};
 
struct Derived: Base {
    virtual void name() {}
};
 
int main()
{
    D d; // 最终派生对象
    A& a = d; // 向上转型，可以用 dynamic_cast，但不必须
    D& new_d = dynamic_cast<D&>(a); // 向下转型
    B& new_b = dynamic_cast<B&>(a); // 侧向转型
 
 
    // Base* b1 = new Base;
    // if(Derived* d = static_cast<Derived*>(b1))
    // {
    //     std::cout << "downcast from b1 to d successful\n";
    //     d->name(); // 可以安全调用
    // } //出问题了。
 
    Base* b2 = new Derived;
    if(Derived* d = static_cast<Derived*>(b2))
    {
        std::cout << "downcast from b2 to d successful\n";
        d->name(); // 可以安全调用
    }
 
    //delete b1;
    delete b2;
    return 0;
}

/**
 * move构造函数
 * https://www.zhihu.com/question/278344922
 * https://www.jianshu.com/p/cb82c8b72c6b 
 **/ 