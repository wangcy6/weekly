#include <iostream>  
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;



class MemoryBlock  
{  
public:  
  
    // 构造器（初始化资源）  
    explicit MemoryBlock(size_t length)  
        : _length(length)  
        , _data(new int[length])  
    {  
         cout<< " MemoryBlock(size_t length)  "<<_length <<endl;
    }  
  
    // 析构器（释放资源）  
    ~MemoryBlock()  
    {  
        if (_data != nullptr)  
        {  
            delete[] _data;  
        }  
    }  
  
    // 拷贝构造器（实现拷贝语义：拷贝that）  
    MemoryBlock(const MemoryBlock& that)  
        // 拷贝that对象所拥有的资源  
        : _length(that._length)  
        , _data(new int[that._length])  
    {    
        std::copy(that._data, that._data + _length, _data);  


         cout<< " MemoryBlock(const MemoryBlock& that) "<<_data <<endl;
        cout<< " MemoryBlock(const MemoryBlock& that)  "<<that._data <<endl;
    }  
  
    // 拷贝赋值运算符（实现拷贝语义：释放this ＋ 拷贝that）  
    MemoryBlock& operator=(const MemoryBlock& that)  
    {  
        if (this != &that)  
        {  
            // 释放自身的资源  
            delete[] _data;  
  
            // 拷贝that对象所拥有的资源  
            _length = that._length;  
            _data = new int[_length];  
            std::copy(that._data, that._data + _length, _data);  
        }  
        cout<< "operator=(const MemoryBlock& that "<<_data <<endl;
        cout<< "operator=(const MemoryBlock& that "<<that._data <<endl;
        return *this;  
    }  
  
    // 移动构造器（实现移动语义：移动that）  
    MemoryBlock(MemoryBlock&& that)  
        // 将自身的资源指针指向that对象所拥有的资源  
        : _length(that._length)  
        , _data(that._data)  
    {  
        // 将that对象原本指向该资源的指针设为空值  
        that._data = nullptr;  
        that._length = 0;  

        cout<< "MemoryBlock(MemoryBlock&& that) _data "<<_data <<endl;
        cout<< "MemoryBlock(MemoryBlock&& that) that._data "<<that._data <<endl;
    }  
  
    // 移动赋值运算符（实现移动语义：释放this ＋ 移动that）  
    MemoryBlock& operator=(MemoryBlock&& that)  
    {  
        if (this != &that)  
        {  
            // 释放自身的资源  
            delete[] _data;  
  
            // 将自身的资源指针指向that对象所拥有的资源  
            _data = that._data;  
            _length = that._length;  
  
            // 将that对象原本指向该资源的指针设为空值  
            that._data = nullptr;  
            that._length = 0; 
             cout<< "_data"<<_data <<endl;
             cout<< "that._data"<<that._data <<endl;
        }  
        return *this;  
    }  
private:  
    size_t _length; // 资源的长度  
    int* _data; // 指向资源的指针，代表资源本身  
};  
  
MemoryBlock f() { return MemoryBlock(50); }  
  
int main()  
{   
   

    //MemoryBlock a = f();            // 调用移动构造器，移动语义  
    //MemoryBlock b = a;              // 调用拷贝构造器，拷贝语义  
    
    //MemoryBlock c = std::move(a);   // 调用移动构造器，移动语义  
    
    // a = f();                        // 调用移动赋值运算符，移动语义  
    // b = a;                          // 调用拷贝赋值运算符，拷贝语义  
    // c = std::move(a);               // 调用移动赋值运算符，移动语义  
    
    //一个swap就能解决的事情 被你们搞得那么麻烦
    int foo=10;
    int& bar=foo;
    int* bara=&bar;
    cout<< "bar="<<bar<<"=="<<*bara<<endl; //42
    bar=0;
    cout<< "bar="<<bar<<"=="<<*bara<<endl; //42
    //int&& baz = foo;       // Err: foo 可以是左值，所以不能将它绑定在右值引用上 error: cannot bind ‘int’ lvalue to ‘int&&’


    int&& qux = 42;        // OK: 将右值 42 绑定在右值引用上
    int* aaa=&qux;
    cout<< "qux="<<qux<<"=="<<*aaa<<endl; //42
    qux =0;
    cout<< "qux="<<qux<<"=="<<*aaa<<endl; //42

    
    int&& quux = foo * 1;  // OK: foo * 1 的结果是一个右值，将它绑定在右值引用
    


    //
}  

//https://liam.page/2016/12/11/rvalue-reference-in-Cpp/
//在 C++ 中，有两种对对象的引用：左值引用和右值引用。



class ResourceOwner {
public:
  ResourceOwner(const char res[]) {
    theResource = new string(res);
  }

  ResourceOwner(const ResourceOwner& other) {
    printf("copy %s\n", other.theResource->c_str());
    theResource = new string(other.theResource->c_str());
  }

  ResourceOwner& operator=(const ResourceOwner& other) {
    ResourceOwner tmp(other);
    swap(theResource, tmp.theResource);
    printf("assign %s\n", other.theResource->c_str());
  }

  ~ResourceOwner() {
    if (theResource) {
      printf("destructor %s\n", theResource->c_str());
      delete theResource;
    }
  }
private:
  string* theResource;
};

void testCopy() {
 // case 1
  printf("=====start testCopy()=====\n");
  ResourceOwner res1("res1");
  ResourceOwner res2 = res1;
  //copy res1
  printf("=====destructors for stack vars, ignore=====\n");
}

void testAssign() {
 // case 2
  printf("=====start testAssign()=====\n");
  ResourceOwner res1("res1");
  ResourceOwner res2("res2");
  res2 = res1;
 //copy res1, assign res1, destrctor res2
  printf("=====destructors for stack vars, ignore=====\n");
}

void testRValue() {
 // case 3
  printf("=====start testRValue()=====\n");
  ResourceOwner res2("res2");
  res2 = ResourceOwner("res1");
 //copy res1, assign res1, destructor res2, destructor res1
  printf("=====destructors for stack vars, ignore=====\n");
}

// int main() {
//   testCopy();
//   testAssign();
//   testRValue();
//   return 0;
// }