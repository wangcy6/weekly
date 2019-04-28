#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//函数对象
//函数对象通常不定义构造函数和析构函数，所以在构造和析构时不会发生任何问题
//()”操作符表示的是一个函数调用符号
struct myclass {
  bool operator()(int i,int j) 
  { 
	return  i<=j;
  }
} myobject;
//仿函数
bool compare(int a, int b)
{
    return a >= b;
}


struct Sum
{
    Sum(): sum{0} {  cout << " construct " << endl;}
    void operator()(int n) 
    {   
        cout << "operator()" << endl; 
        sum += n; 
    }
    int sum;
};

auto compare = [](const Base &a, const Base &b) {
                     return a.variable < b.variable;};
					 
//g++ -g -std=c++11 algorithm_sort.cpp
int main()
{
   vector<int> myvector;
   
    for (int i = 0; i < 17; i++)
    {
        myvector.push_back(i);
	    //myvector.push_back(0);
    }
 
	
	std::sort (myvector.begin(), myvector.end(), compare);
	std::sort (myvector.begin(), myvector.end(), [](int x,int y){ return x<y;});
	for (auto n : myvector) 
	{
		cout << n << " ";
	}
	cout << endl;
	
	
	
	return 0;
}

auto compare = [](const <vector<int> &a, const <vector<int> &b) {
                     if (a[0]<b[0])
					 {
						 return a[0]<b[0]
					 }else if(a[1]<b[1])
					 {
						return a[1]<b[1]
					 }						 
					 };
					 
