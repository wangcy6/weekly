#include <cassert>
#include <iostream>
#include "c0407.h"

const int increment = 100;

void Stash::initialize(int sz)
{
size = sz; 
quantity = 0;
storage = 0;
next = 0;
}

int Stash::add(const void* element)
{
if(next >= quantity)
inflate(increment);

int startBytes = next * size;
for(int i = 0 ; i < size; i++)
{
storage[startBytes + i] = ((unsigned char*)element)[i];
}
next++;
return (next - 1);
}

int Stash::count()
{
return next;
}

void* Stash::fetch(int index)
{
assert(index >= 0);
if(index >= next)
return 0;
return &(storage[size * index]);
}

void Stash::inflate(int increase)
{
assert(increase > 0);
int newQuantity = quantity + increase;
int newBytes = newQuantity * size;
int oldBytes = quantity * size;
unsigned char * b = new unsigned char[newBytes];
for(int i = 0 ; i < oldBytes; i++)
b[i] = storage[i];
delete []storage;
storage = b;
quantity = newQuantity;
}

void Stash::cleanup()
{
if(storage != 0)
{
std::cout<<"Freeing storage"<<std::endl;
delete []storage;
}
}

