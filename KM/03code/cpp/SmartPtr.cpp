//https://my.oschina.net/costaxu/blog/103119

//https://www.boost.org/doc/libs/1_71_0/libs/smart_ptr/doc/html/smart_ptr.html
//https://www.boost.org/doc/libs/1_63_0/libs/smart_ptr/smart_ptr.htm
//https://github.com/boostorg/smart_ptr

//http://blog.leanote.com/post/shijiaxin.cn@gmail.com/C-shared_ptr

#include<iostream>
using namespace std;

class _counter{
public:
    _counter(int u):count(u){}
    ~_counter(){}
    int count;
};
template<typename T>
class smart_ptr{
    bool is_empty() const{
        return pt==nullptr;
    }
    void clear(){
        if(pt==nullptr){
            return ;
        }
        pc->count--;
       
        cout<<"clear "<< pt <<" count="<<pc->count<<endl;

        if(pc->count==0){
            delete pt;
            delete pc;
        }
        pc = nullptr;
        pt = nullptr;
    }
public:
    smart_ptr(){
        pc = nullptr;
        pt = nullptr;
    }
    smart_ptr(T *t){
        //bug1 when new failed
        if(t==nullptr){
            pc = nullptr;
            pt = nullptr;
            return ;
        }
        //bug2 new failed 
        pc =new _counter(1);
        pt = t;
        cout<<pt <<" count="<<pc->count<<endl;
    }
    smart_ptr(const smart_ptr<T>& rhs){
        pc = rhs.pc;
        pt = rhs.pt; 
        if(rhs.is_empty()){
            return ;
        }
        pc->count++;
         cout<<pt <<" count="<<pc->count<<endl;
    }
    smart_ptr<T>& operator=(const smart_ptr<T>& rhs){
        if(&rhs == this){
            return *this;
        }
        clear();
        if(rhs.is_empty()){
            return *this;
        }
        pc = rhs.pc;
        pt = rhs.pt;
        pc->count++;
         cout<<pt <<" count="<<pc->count<<endl;
        return *this;
    }
    ~smart_ptr(){
        clear();
    }
    _counter* pc;
    T* pt;
    T* operator->(){
        return pt;
    }
};

// class myClass{
// public:
//     myClass(){cout<<"Create"<<endl;}
//     ~myClass(){cout<<"Delete"<<endl;}
// };

class myClass{
public:
    smart_ptr<myClass> parent;
    smart_ptr<myClass> child;
    string name;
    myClass(string name):name(name){cout<<"Create "<<name<<endl;};
    ~myClass(){cout<<"Delete "<<name<<endl;}
};

void test_myclass()
{
    smart_ptr<myClass> p1(new myClass("a"));
    smart_ptr<myClass> p2(new myClass("bb"));
    p1->child=p2;
    p2->parent=p1;
}
int main(){
    test_myclass();
}



// //模板类作为友元时要先有声明
//     template <typename T>
//     class SmartPtr;
    
//     template <typename T>
//     class U_Ptr     //辅助类
//     {
//     private:
//         //该类成员访问权限全部为private，因为不想让用户直接使用该类
//         friend class SmartPtr<T>;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类
    
//         //构造函数的参数为基础对象的指针
//         U_Ptr(T *ptr) :p(ptr), count(1) { }
    
//         //析构函数
//         ~U_Ptr() { delete p; }
//         //引用计数
//         int count;   
    
//         //基础对象指针
//         T *p;                                                      
//     };
    
//     template <typename T>
//     class SmartPtr   //智能指针类
//     {
//     public:
//         SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) { }      //构造函数
//         SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) { ++rp->count; }  //复制构造函数
//         SmartPtr& operator=(const SmartPtr<T>& rhs) {    //重载赋值操作符
//             ++rhs.rp->count;     //首先将右操作数引用计数加1，
//             if (--rp->count == 0)     //然后将引用计数减1，可以应对自赋值
//                 delete rp;
//             rp = rhs.rp;
//             return *this;
//         }
    
//         T & operator *()        //重载*操作符  
//         {
//             return *(rp->p);
//         }
//         T* operator ->()       //重载->操作符  
//         {
//             return rp->p;
//         }
    
    
//         ~SmartPtr() {        //析构函数
//             if (--rp->count == 0)    //当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
//                 delete rp;
//             else 
//             cout << "还有" << rp->count << "个指针指向基础对象" << endl;
//         }
//     private:
//         U_Ptr<T> *rp;  //辅助类对象指针
//     };