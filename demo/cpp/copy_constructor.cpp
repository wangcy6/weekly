#include <string>
#include <iostream>

using namespace std;
//tmp://zhibo.gome.com.cn:1935/live/616?token=d2c63231f04ac154d0a425b14a3c3088
class Person
{
public:
	Person(){ cout << "Person() Constructor" << endl;}
	Person(const Person& p)
	{
		cout << "Person(const Person& p) Copy Constructor" << endl;
	}
   //为什么在C++中拷贝构造函数为什么不能是对象值传递，而必须是引用或者指针呢？
   //自己错误理解纠正：自己理解成只能是引用，不能用指针，今天测试一下 还是指针是可以的。
   Person(const Person* p)
   {
       cout << "Person(const Person* p) Copy Constructor" << endl;
   }
	Person& operator=(const Person& p)
	{
		cout << "Assign" << endl;
		return *this;
	}

private:
	int age;
	string name;
};
int main()
{  
    Person p;
    Person p1(&p);
    return 0;
}