#ifndef _MEM_H
#define _MEM_H
#pragma once

typedef unsigned char byte;

class Mem{
	byte* mem;
	int size;
	void ensureMinsize(int minsize);
	public:
	Mem();
	Mem(int sz);
	~Mem();

	int msize();
	byte* pointer();
	byte* pointer(int minSize);
};


#endif //_MEM_H
