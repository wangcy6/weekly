#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>
#include <cstdlib>

using namespace std;
//10w
const int num = 100000;

class timer {
public:
	clock_t start;
	clock_t end;
	string name;
	timer(string n) {
		start = clock();
		name = n;
	}
	~timer() {
		end = clock();
		printf("%s time: %f \n", name.c_str(), 
			(end - start) * 1.0 / CLOCKS_PER_SEC * 1000);
	}
};

template<typename T> 
void insert(T & conta, string name) {
	srand((unsigned)time(NULL));  
	timer t1(name);
	for (int i = 0; i < num / 2; i++) {
		int key = rand();
		conta.insert(pair<int, int>(i, i));
		conta.insert(pair<int, int>(key, i));
	}

}

template<typename T>
void find(T & conta, string name) {
	srand((unsigned)time(NULL));  
	timer t1(name);
	for (int i = 0; i < num / 2; i++) {
		int key = rand();
		conta.find(key);
		conta.find(i);
	}
}

template<typename T>
void erase(T & conta, string name) {
	srand((unsigned)time(NULL));  
	timer t1(name);
	for (int i = 0; i < num / 2; i++) {
		conta.erase(i);
		int key = rand();
		conta.erase(key);
	}
}


void test_map() 
{
	map<int, int> m1;
	insert<map<int, int> >(m1, "map insert");
	find<map<int, int> >(m1, "map find");	
	erase<map<int, int> >(m1, "map erase");
}

void test_unordered_map() 
{
	unordered_map<int, int> m2;
	insert<unordered_map<int, int> >(m2, "unordered_map insert");	
	find<unordered_map<int, int> >(m2, "unordered_map find");
	erase<unordered_map<int, int> >(m2, "unordered_map erase");
}
//g++ -g  -std=c++11 unordered_map.cpp
int main()
{
	test_map();
	test_unordered_map();
	return 0;
}