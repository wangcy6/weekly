#ifndef _STACKOFINT_H
#define _STACKOFINT_H

class StackOfInt
{
	class StackImp;
	StackImp *stackimp;
	public:
	void initialize(int sz);
	void cleanup();
	int	 fetch(int index);
	void set(int index, int val);
	void add(const int i);
};

#endif //_STACKOFINT_H
