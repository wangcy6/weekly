#ifndef _STASH_H
#define _STASH_H
#pragma once

#include "c0709.h"

class Stash {
	int size;
	int quantity;
	int next;
	Mem *storage;
	void inflate(int increase);
	public:
	Stash(int sz, int initQuantity = 0);
	~Stash();

	int add(void* element);
	void *fetch (int index);
	int count();
};


#endif // _STASH_H
