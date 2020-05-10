#include "Mem.h"
#include <cstring>

Mem::Mem()
{
	mem = 0;
	size = 0;
}

Mem::Mem(int sz)
{
	mem = 0; 
	size = 0;
	ensureMinsize(sz);
}

Mem::~Mem()
{
	delete []mem;
}

int Mem::msize()
{
	return size;
}

void Mem::ensureMinsize(int minSize)
{
	if(size < minSize)
	{
		byte* newmem=  new byte[minSize];
		memset(newmem + size, 0, minSize - size);
		memcpy(newmem, mem, size);
		delete []mem;
		mem = newmem;
		size = minSize;
	}
}

byte* Mem::pointer()
{
	return mem;
}
 byte* Mem::pointer(int minSize)
{
	ensureMinsize(minSize);
	return mem;
}
