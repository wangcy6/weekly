#include "c0707.h"
#include <iostream>

using namespace std;

Stack::Link::Link(void* dat, Link* nxt)
{
	data = data;
	next = nxt;
}

Stack::Link::~Link()
{}


Stack::Stack()
{
	head = 0;
}

Stack::Stack(int* arr, int length)
{
//	Stack* stack = new Stack();
//	head = 0;
//	for(int i = 0; i < length; i++)
//	{
//		stack.push(&(arr[i]));
//	}
	head = 0;
	for(int i = 0; i < length; i++)
	{
		push((void*)&(arr[i]));
	}

}


void Stack::push(void* dat)
{
//	Link* newLink = new Link(dat,head);
//	newLink->data = dat;
//	head->next = newLink;
//	head = newLink;
	head = new Link(dat,head);
}

void* Stack::peek()
{
	if(head != 0)
	  return head->data;
}

void* Stack::pop()
{
	void* olddata = head->data;
	Link* old = head;
	head = head->next;
	delete old;
	return olddata;
}
Stack::~Stack()
{
	if(head == 0)
	{
		cout<<"Stack not empty!!"<<endl;
	}
}
