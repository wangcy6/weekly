#ifndef _ASTEROID_H
#define _ASTEROID_H
#include "PStash.h"

class Asteroid: public PStash{
	public:
	int add(Asteroid* element)
	{
		return PStash::add((void*)element);
	}
	Asteroid* operator[](int index)
	{
		return (Asteroid*)PStash::operator[](index);
	}
	Asteroid* remove(int index)
	{
		return (Asteroid*)PStash::remove(index);
	}

	int count() const
	{
		return PStash::count();
	}

};

#endif// _ASTEROID_H
