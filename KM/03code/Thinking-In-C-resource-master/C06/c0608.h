#ifndef STACK_H
#define STACK_H

class Stack {
	class Link {
		void* data;
		Link* next;
		public:
		friend Stack;
		Link(void* dat, Link* nxt);
		~Link();
	}* head;
	public:
	Stack();
	~Stack();
	void push(void* dat);
	void* peek();
	void* pop();
};
#endif // STACK_H ///:~
