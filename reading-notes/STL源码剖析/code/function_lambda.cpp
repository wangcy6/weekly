#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//函数对象
struct Sum
{
    Sum(): total{0} 
    {
        cout << " construct " << endl; 
    }
    void operator()(int x) 
    {   
        cout << "operator()" << x《《 endl; 
        total += x; 
    }
    int total;
};

//g++ -g -std=c++11 algorithm_for_each.cpp
int main()
{
   vector<int> myvector;
    for (int i = 0; i < 17; i++)
    {
        myvector.push_back(i);
	 
    }

	//Lambda 
	int total = 0;
	std::for_each(myvector.begin(), myvector.end(), [&total](int x) { total += x; });
	std::cout <<"Lambda: "<< total<<endl;
	
   // calls Sum::operator() for each number
    Sum s = std::for_each(myvector.begin(), myvector.end(), Sum());
	std::cout << "sum: " << s.total <<endl;


    cout<<[]{return 42;}()<<endl;

	return 0;
}
