#ifndef _STASH_H
#define _STASH_H
#pragma once

class Stash{
	int size;
	int quantity;
	int next;
	unsigned char* storage;

	void inflate(int increase);
	public:

	Stash(int sz, int initQuantity = 0);
	~Stash();

	int add(void* element);
	void* fetch(int index);
	int count();
};


#endif //_STASH_H
