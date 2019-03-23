#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//函数对象
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
