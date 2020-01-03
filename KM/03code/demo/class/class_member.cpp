#include <iostream>
using namespace std;


class Person{
public:
    Person(string& str,int x): name(str),value(x){ }

    string & name;
    const int value;
};

class Grandparent {
 public:
  Grandparent(int no): grandparent_data(no){}
  void printRef() {
            cout << "myref is: " << grandparent_data << endl;
        }
  Grandparent& operator =(const Grandparent& other )
  { 
    
    this->grandparent_data =other.grandparent_data; //why 不报错。
    cout <<" this->grandparent_data="<< this->grandparent_data <<"other.grandparent_data="<<other.grandparent_data<<endl;
    return *this;
  }
  private:
  int &grandparent_data;
};

int main() {
    

    string s1 = "A", s2 = "B";
    Person p1(s1,1),p2(s2,2);
    Person p3(p2);            //拷贝构造函数可以正常调用，和预期结果一样。

    cout << p1.name << " " << p1.value << endl;        //A 1
    cout << p2.name << " " << p2.value << endl;        //B 2
    cout << p3.name << " " << p3.value << endl;        //B 2

    //p1 = p2;    //编译错误


    int b=10;
    int& c=b;
    c=12;
    Grandparent gt1(1);
    gt1.printRef();
    
    Grandparent gt2(13);
    gt2.printRef();
    
    Grandparent gt3(gt1); //见鬼了 输出的有问题
    gt3.printRef();

    gt2 =gt1;
    gt2.printRef();

    //error: non-static reference member ‘int& Grandparent::grandparent_data’, can’t use default assignment operator

 
}
