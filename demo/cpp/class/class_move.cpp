#include <iostream>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstring>
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
    
     // 构造器（初始化资源）  
    explicit MemoryBlock(string temp)  
        : _length(temp.length())  
        , _data(new int[temp.length()])  
    {  
         cout<< " MemoryBlock(size_t length)  "<<_length <<endl;

         memcpy(_data, temp.c_str(), temp.length());
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


         cout<< "111 MemoryBlock(const MemoryBlock& that) "<<_data <<endl;
        
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

        cout<< "MemoryBlock(MemoryBlock&& that) _data "<<_data << ":"<<that._data<< endl;
        
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

             cout<< " 33  operator=(MemoryBlock&& that) "<<_data <<endl;
            cout<< " 33  operator=(MemoryBlock&& that) "<<that._data <<endl;
        }  
        return *this;  
    }
  int* getData()
  { 
    if (nullptr ==_data)
   {
        return nullptr;
   } 
   return _data;

  }  
public:  
    size_t _length; // 资源的长度  
    int* _data; // 指向资源的指针，代表资源本身  
};  
  
MemoryBlock f() { return MemoryBlock(50); }  

void testMove(){
  
  MemoryBlock copy("hello"); //调用构造函数
  
  MemoryBlock&& nocopy= std::move(copy); //类型转换：右值引用(其实就是引用 MemoryBlock& nocopy=copy;)，这里没有copy，在值类型参数传递时候，减少一次临时copy。值类型最终还是copy走了 vector<int> copy
  //FQA1 写&& 多麻烦，既然是引用，为什么不写&，说明：函数原型是定义值，不然就是指针类型。

  MemoryBlock move=std::move(copy); //MemoryBlock move(std::move(copy)) 调用移动拷贝构造函数，移动语义， 创建新对象，消耗old对象，
  //FQA2 移动语义和类型转换不是一个意思 移动语义swap交换。用法上约定 && 来实现 移动，其实&可完成这个功能。c++新增新功能，不影响老使用方式。
  //构造函数具体怎么实现，具体些代码人控制的。&本身是无法修改的。修改保护指针的类对象。

  if (nullptr ==copy.getData())
  {
   cout<<"copy is moved"<<endl;
  }else
  {
    cout<<"copy: "<<copy._length <<":"<<*copy._data<<endl; 
    //Segmentation fault swap(null,copy) 移动语义， 创建新对象，消耗old对象 copy._dat类型private改为public。没有封装  ，一般采用公共接口方式
  }
  
  
  cout<<"move: "<<move._length <<":"<<*move._data<<endl;


}
int main()  
{   
   
    testMove();
    //MemoryBlock a = f();            // 调用移动构造器，移动语义  
    //MemoryBlock b = a;              // 调用拷贝构造器，拷贝语义  
    
    //MemoryBlock c = std::move(a);   // 调用移动构造器，移动语义  
    
    // a = f();                        // 调用移动赋值运算符，移动语义  
    // b = a;                          // 调用拷贝赋值运算符，拷贝语义  
    // c = std::move(a);               // 调用移动赋值运算符，移动语义  
    
    //一个swap就能解决的事情 被你们搞得那么麻烦
    // int foo=10;
    // int& bar=foo;
    // int* bara=&bar;
    // cout<< "bar="<<bar<<"=="<<*bara<<endl; //42
    // bar=0;
    // cout<< "bar="<<bar<<"=="<<*bara<<endl; //42
    // //int&& baz = foo;       // Err: foo 可以是左值，所以不能将它绑定在右值引用上 error: cannot bind ‘int’ lvalue to ‘int&&’


    // int&& qux = 42;        // OK: 将右值 42 绑定在右值引用上
    // int* aaa=&qux;
    // cout<< "qux="<<qux<<"=="<<*aaa<<endl; //42
    // qux =0;
    // cout<< "qux="<<qux<<"=="<<*aaa<<endl; //42

    
    // int&& quux = foo * 1;  // OK: foo * 1 的结果是一个右值，将它绑定在右值引用
    


    //
}  

//https://liam.page/2016/12/11/rvalue-reference-in-Cpp/
//在 C++ 中，有两种对对象的引用：左值引用和右值引用。
