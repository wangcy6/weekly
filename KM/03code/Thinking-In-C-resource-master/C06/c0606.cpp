#include "c0606.h"

//Define Handle`s implementation:
struct Handle::Cheshire
{
	int i;
};

Handle::Handle()
{
	smile = new Cheshire;
	smile->i = 0;
}

Handle::~Handle()
{
	delete smile;
}

int Handle::read()
{
	return smile->i;
}

void Handle::change(int i)
{
	smile->i = i;
}
