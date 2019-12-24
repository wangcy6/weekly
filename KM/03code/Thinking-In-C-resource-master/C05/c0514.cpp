#include <iostream>
#include <vector>
#include "c0514.h"

using namespace std;

class StackOfInt::StackImp
{
	friend StackOfInt;
	int m_size;
	int m_maxsize;
	vector<int> m_v;
	public:
	void initialize(int sz);
	void push(const int i);
	void set(int index, int val);
	int  get(int index);
};

//StackImp
void StackOfInt::StackImp::initialize(int sz)
{
	m_size  = 0;
	m_maxsize = sz;
}
void StackOfInt::StackImp::push(const int i)
{
	if(m_size < m_maxsize)
	{
	m_v.push_back(i);
	m_size += 1;
	}
	else
	{
		cout<<"Out of Size!!!"<<endl;
	}
}
void StackOfInt::StackImp::set(int index, int val)
{
	if(index <= m_size && index >= 0)
	  m_v[index] = val;
	else
	  cout<<"Out of range!"<<endl;
}
int StackOfInt::StackImp::get(int index)
{
	if(index <= m_size && index >= 0)
	return m_v[index];
	else
	  cout<<"Out of Range!!"<<endl;
	return 0;
}

//Handle
void StackOfInt::initialize(int sz)
{
	stackimp = new StackImp;
//set the maxsize:  stackimp->m_maxsize = sz; or as follows:
	stackimp->initialize(sz);
}

void StackOfInt::cleanup()
{
	stackimp->m_v.clear();
	delete stackimp;
}
int StackOfInt::fetch(int index)
{
	return (stackimp->get(index));
}

void StackOfInt::set(int index, int val)
{
	stackimp->set(index,val);
}

void StackOfInt::add(const int i)
{
	stackimp->push(i);
}
