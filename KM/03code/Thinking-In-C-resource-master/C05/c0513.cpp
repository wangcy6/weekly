#include "c0513.h"

//Define Handle`s implementation:
struct Handle::Cheshire
{
	int i;
};

void Handle::initialize()
{
	smile = new Cheshire;
	smile->i = 0;
}

void Handle::cleanup()
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
