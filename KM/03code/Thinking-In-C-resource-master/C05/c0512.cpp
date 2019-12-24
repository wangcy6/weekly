#include "c0512.h"
#include <iostream>

using namespace std;

void Stack::Link::initialize(void* dat, Link* nxt)
{
	data = dat;
	next = nxt;
}

void Stack::initialize()
{
	head = 0;
}

void Stack::push(void * dat)
{
	Link* newLink = new Link;
	newLink->initialize(dat,head);
	head = newLink;
}

void* Stack::peek()
{
	if(head == 0)
	{
		std::cout<<"Stack empty!"<<std::endl;
		return 0;
	}
	return head->data;
}

void* Stack::pop() {
	  if(head == 0) return 0;
	    void* result = head->data;
		  Link* oldHead = head;
		    head = head->next;
			  delete oldHead;
			    return result;
}

void Stack::cleanup()
{
	if(head != 0)
	{
		std::cout<<"Stack not empty!"<<std::endl;
	}
}
