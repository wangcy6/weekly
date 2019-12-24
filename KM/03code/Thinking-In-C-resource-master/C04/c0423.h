#ifndef _STACK_STASH_H
#define _STACK_STASH_H
#pragma once

#include "c0407.h"
#include "c0408.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

typedef struct stack_stash{
	int m_quantity;
	int m_next;
	Stack m_stack;
	Stash* m_ptrStash;
	std::string m_fileName;
	std::ifstream m_in;

	void initialize(std::string filenName);
	void inflate(int increase);
	void addLine();
	void fetch(int index);
	void cleanup();

} StackSth;



#endif//_STACK_STASH_H
