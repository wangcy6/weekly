#ifndef _STACK_H
#define _STACK_H
#pragma once

class Stack{
	struct Link{
		void * data;
		Link* next;
		Link(void* data, Link* next);
		~Link();
	}* head;

	public:

	Stack();
	Stack(int* arr, int length);
	~Stack();
	void push(void * data);
	void* peek();
	void* pop();

};

#endif //_STACK_H
