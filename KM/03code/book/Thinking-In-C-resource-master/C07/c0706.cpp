#include <iostream>
#include <cassert>
#include "c0706.h"

using namespace std;

const int increament = 100;

Stash::Stash(int sz, int initQuantity)
{
	size = sz;
	quantity = 0;
	next = 0;
	storage = 0;
	inflate(initQuantity);
}

Stash::~Stash()
{
	if(storage != 0)
	{
		cout<<"delete storage!"<<endl;
		delete []storage;
	}
}

void Stash::inflate(int increase)
{
	assert(increase >= 0);
	if(increase == 0)
	  return;
	int newQuantity = quantity + increase;
	unsigned char* newStorage = new unsigned char[size*newQuantity];
	for(int i = 0; i < quantity * size; i++)
	{
		newStorage[i] = storage[i];
	}
	delete []storage;
	storage = newStorage;
	quantity = newQuantity;
	cout<<"inflate quantity = "<<quantity<<endl;

}

int Stash::add(void *element)
{
	if(next >= quantity)
	  inflate(increament);
	unsigned char* e = (unsigned char*)element;
	for(int i = 0; i < size; i++)
	{
		storage[i + next*size] = e[i];
	}
	next++;
	return (next - 1);

}

void* Stash::fetch(int index)
{
	assert(index >= 0);
	if(index >= next)
	  return 0;
	return (&storage[index * size]);
}
int Stash::count()
{
	return next;
}
