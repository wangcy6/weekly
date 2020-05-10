#include <iostream>
#include <vector>
#include <string>

using namespace std;

class StringVector: public vector<void*>{
	public:
	void push_back(const string* s)	
	{
		vector<void*>::push_back((void*)s);
	}

	string* operator[] (size_type n)
	{
		return (string*)vector<void*>::operator[](n);
	}
};

int main()
{
	StringVector sV;
	string s("hi!");
	string s1("hi what?!");
	string s2("hi you!");
	void* vp = (void*) &s;
	sV.push_back(&s);
	sV.push_back(&s1);
	sV.push_back(&s2);
	//sV.push_back(vp);error invalid conversion from ‘void*’ to ‘const string*'
}
