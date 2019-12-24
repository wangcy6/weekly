#include "c0423.h"

using namespace std;

const int increment  = 100;

void StackSth::initialize(string fileName)
{
	m_quantity = 0;
	m_next = 0;
	m_ptrStash = 0;
	m_fileName = fileName;
	m_in.open(m_fileName.c_str());
}

void StackSth::inflate(int increase)
{
	assert(increase > 0);

	int newQuantity = m_quantity + increase;
	Stash* p = new Stash[newQuantity];

	for(int i = 0 ; i < m_quantity; i++)
	{
		p[i] = m_ptrStash[i];
	}
	delete []m_ptrStash;
	m_ptrStash = p;
	m_quantity = newQuantity;
}

void StackSth::addLine()
{
	if(m_quantity <= m_next)
	  inflate(increment);
	string line;
	if(getline(m_in,line))
	{
		m_ptrStash[m_next].initialize(sizeof(char));
		for(int i  = 0; i < line.size(); i++)
		{
		  m_ptrStash[m_next].add((void*)&line[i]);
		}
		char e = '\n';
		m_ptrStash[m_next].add((void*)&e);
		m_next++;
		m_stack.push((void*)&m_ptrStash[m_next]);
	}

}
void StackSth::fetch(int index)
{
	assert (index >= 0);
	if(index <= m_next)
	{
		for(int j = 0; j < m_ptrStash[index].count();j++)
		{
			cout<<*(char*)(m_ptrStash[index].fetch(j));
		}
	}
	else
	{
		cout<<"Out of file!!"<<endl;
	}
}

void StackSth::cleanup()
{
	m_stack.cleanup();
}
