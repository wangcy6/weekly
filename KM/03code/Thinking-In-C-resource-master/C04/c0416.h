#ifndef _STASH_VECTOR_H
#define _STASH_VECTOR_H
#pragma once
#include <vector>
typedef struct Stash
{
	int size;
	int next;

	std::vector<char> storage;

	void initialize(int size);
	void cleanup();

	int add(const void* element);
	void* fetch(int index);
	int count();
} VStash;
#endif//_STASH_VECTOR_H
