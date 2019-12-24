#include "c0425.h"
#include <iostream>

using namespace std;

void Link::Creat(int size)
{
	head = new Node;
	Node *p = head;
	for(int i = 0; i < size; i++)
	{
		Node* newNode = new Node;
		newNode->data = i;
		p->next = newNode;
		p = newNode;
	}
	p->next = 0;
}

void Link::display()
{
	Node* node = head;
	while(node)
	{
		cout<<"Node value = "<<node->data<<endl;
		node = node->next;
	}
}

void Link::cleanup()
{
	while(head)
	{
		Node* endNode  = head;
		cout<<"delte Node->data = "<<endNode->data<<endl;
		head = head->next;
		delete endNode;
	}
}

int main()
{
	Link lsy;
	lsy.Creat(20);
	lsy.display();
	lsy.cleanup();
}
