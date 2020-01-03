#include<iostream>
using namespace std;

class _counter{
public:
    _counter(int u,int v):count(u),count_weak(v){}
    ~_counter(){}
    int count;
    int count_weak;
};
template<typename T>
class smart_ptr{
    void clear(){
        if(pt==nullptr){
            return ;
        }
        pc->count--;
        if(pc->count==0){
            delete pt;
        }
        if(pc->count==0 && pc->count_weak==0){
            delete pc;
        }
        pc = nullptr;
        pt = nullptr;
    }
public:
    bool is_empty() const{
        return pt==nullptr;
    }
    smart_ptr(){
        pc = nullptr;
        pt = nullptr;
    }
    smart_ptr(T *t){
        if(t==nullptr){
            pc = nullptr;
            pt = nullptr;
            return ;
        }
        pc =new _counter(1,0);
        pt = t;
    }
    smart_ptr(const smart_ptr<T>& rhs){
        pc = rhs.pc;
        pt = rhs.pt;
        if(rhs.is_empty()){
            return ;
        }
        pc->count++;
    }
    smart_ptr<T>& operator=(const smart_ptr<T>& rhs){
        if(&rhs == this){
            cout<<"the same"<<endl;
            return *this;
        }
        clear();
        if(rhs.is_empty()){
            return *this;
        }
        pc = rhs.pc;
        pt = rhs.pt;
        pc->count++;
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
template<typename T>
class smart_ptr_weak{
    bool is_empty() const{
        return pt==nullptr;
    }
    void clear(){
        if(pt==nullptr){
            return ;
        }
        pc->count_weak--;
        if(pc->count==0 && pc->count_weak==0){
            delete pt;
            delete pc;
        }
        pc = nullptr;
        pt = nullptr;
    }
public:
    smart_ptr_weak(){
        pc = nullptr;
        pt = nullptr;
    }
    smart_ptr_weak(const smart_ptr<T>& rhs){
        pc = rhs.pc;
        pt = rhs.pt;
        if(rhs.is_empty()){
            return ;
        }
        pc->count_weak++;
    }
    smart_ptr_weak<T>& operator=(const smart_ptr<T>& rhs){
        clear();
        if(rhs.is_empty()){
            return *this;
        }
        pc = rhs.pc;
        pt = rhs.pt;
        pc->count_weak++;
        return *this;
    }
    _counter* pc;
    T* pt;
    smart_ptr<T> lock(){
        smart_ptr<T> tmp;
        if(pc==nullptr||pc->count==0){
            return tmp;
        }
        tmp.pc=pc;
        tmp.pt=pt;
        tmp.pc->count_weak++;
        return tmp;
    }
};

class myClass{
public:
    smart_ptr_weak<myClass> parent;
    smart_ptr<myClass> child;
    string name;
    myClass(string name):name(name){cout<<"Create "<<name<<endl;};
    ~myClass(){cout<<"Delete "<<name<<endl;}
};
int main(){
    smart_ptr<myClass> p1(new myClass("a"));
    smart_ptr<myClass> p2(new myClass("bb"));
    
    p1->child=p2;
    p2->parent=p1;
    auto ptr=p2->parent.lock();
    
    cout<<ptr->name<<endl;
}