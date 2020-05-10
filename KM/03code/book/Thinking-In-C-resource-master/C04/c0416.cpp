#include "c0416.h"
#include <cassert>

void VStash::initialize(int sz)
{
	size = sz;
	next = 0;
}

void VStash::cleanup()
{}

int VStash:: add(const void* element)
{
	for(int i = 0; i < size; i++)
	{
		storage.push_back(((char*)element)[i]);
	}
	next++;
	return (next - 1);
}

void* VStash::fetch(int index)
{
	assert(index >= 0);
	if(index >= next)
	  return 0;
	return &(storage[index * size]);
}

int VStash::count()
{
	return next;
}
