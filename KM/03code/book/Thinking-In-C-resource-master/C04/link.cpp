#include <iostream>

using namespace std;
struct Node{
	int data;
	Node* next;
};



void Creat(Node* head, int size)
{
	Node *p;
	p = head;
	for(int i = 0; i < size; i++)
	{
		Node* newNode = new Node;
		newNode->data = i;
		p->next = newNode;
		p = newNode;
	}
	p->next = 0;

}

void display(Node* node)
{
	while(node)
	{
		cout<<"Node value"<<node->data<<endl;
		node = node->next;
	}
}

void cleanup(Node* node)
{
	while(node)
	{
		Node* endNode  = node;
		cout<<"delte Node"<<endNode->data;
		node = node->next;
		delete endNode;
	}
}


int main()
{
	Node *head  = new Node;
	head->data = -1;
	Creat(head,20);
	display(head);
	cleanup(head);

}
