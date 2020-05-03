#include "c0709.h"
#include <cstring>

using namespace std;

Mem::Mem(int sz)
{
	mem = 0;
	size = 0;
	ensureMinSize(sz);
}

Mem::~Mem()
{
	delete []mem;
}

int Mem::msize()
{
	return size;
}

void Mem::ensureMinSize(int minsize)
{
	if(size < minsize) {
		byte* newmem = new byte[minsize];
		memset(newmem + size, 0, minsize - size);
		memcpy(newmem,mem,size);
		delete []mem;
		mem = newmem;
		size = minsize;
	}
}

byte* Mem::pointer(int minsize)
{
	ensureMinSize(minsize);
	return mem;
}
