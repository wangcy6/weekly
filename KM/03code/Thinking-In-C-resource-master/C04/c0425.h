#ifndef _LINK_H
#define _LINK_H
#pragma once

using namespace std;

struct Link
{
	struct Node{
		int data;
		Node* next;
	} *head;
	void Creat(int size);
	void display();
	void cleanup();
};

#endif //_LINK_H
