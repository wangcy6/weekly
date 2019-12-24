#ifndef MEM2_H
#define MEM2_H
#pragma once

typedef unsigned char byte;

class Mem {
	byte* mem;
	int size;

	void ensureMinSize(int minsize);
	public:
	Mem(int sz = 0);
	~Mem();

	int msize();
	byte* pointer(int minszie = 0);
	bool moved();
};

#endif //MEM2_H
