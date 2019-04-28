#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <time.h>
#include <stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
void uppercasify(const string& str) {}//函数的定义

//函数对象的定义
template <typename T>
class print
{
public:
    void operator()(const T& elem)
    {
        cout<<elem<<" ";
    }
};

int main()
{
	char subtleBookPlug[] = "Effective C++";
	uppercasify(subtleBookPlug);  //类型不同
	
	
	int ia[6]={0,1,2,3,4,5};
    vector<int> iv(ia,ia+6);
    //print<int>()是一个临时对象，这属于对象的构造
    for_each(iv.begin(),iv.end(),print<int>());
	
	
	return 0;
}