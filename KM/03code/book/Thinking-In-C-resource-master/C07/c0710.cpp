#include "c0710.h" 
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

const int increament  = 100;
Stash::Stash(int sz, int initQuantity)
{
	size = sz; 
	quantity = 0;
	next = 0;
	storage = new Mem(initQuantity);
	inflate(initQuantity);
}


Stash::~Stash()
{
	if(storage != 0)
	delete []storage;
}

void Stash::inflate(int increase)
{
	assert(increase >= 0);
	if(increase == 0)
	  return;
	int newQuantity = quantity + increase;
	storage->pointer(newQuantity);
	quantity = newQuantity;
}

int Stash::add(void *element)
{
	if(next >= quantity)
	  inflate(increament);
	strcpy((char*)storage->pointer(),(char*)element);
	next++;
	return (next - 1);

}
void* Stash::fetch(int index)
{
	assert(index >= 0);
	if(index >= next)
	  return 0;
	return (&(storage->pointer()[index * size]));
}

int Stash::count()
{
	return next;
}

