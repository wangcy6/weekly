#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/* template <class Key,                  // unordered_map::key_type
          class T,                    // unordered_map::mapped_type
          class Hash = hash<Key>,     // unordered_map::hasher
          class Pred = equal_to<Key>, // unordered_map::key_equal
          class Alloc =
              allocator<pair<const Key, T>> // unordered_map::allocator_type
          >
class unordered_map */;
// CPP program to demonstrate working of unordered_map
// for user defined data types.

// Objects of this class are used as key in hash
// table. This class must implement operator ==()
// to handle collisions.
struct Person {
  string first, last; // First and last names

  Person(string f, string l) {
    first = f;
    last = l;
  }

  // Match both first and last names in case
  // of collisions.
  bool operator==(const Person &p) const {
    return first == p.first && last == p.last;
  }
};

class MyHashFunction {
public:
  // Use sum of lengths of first and last names
  // as hash function.
  size_t operator()(const Person &p) const {
    return p.first.length() + p.last.length();
  }
};

// g++ -std=c++11 unordered_map_class.cpp
int main() {
  unordered_map<Person, int, MyHashFunction> um;
  Person p1("kartik", "kapoor");
  Person p2("Ram", "Singh");
  Person p3("Laxman", "Prasad");

  um[p1] = 100;
  um[p2] = 200;
  um[p3] = 100;

  for (auto e : um) {
    cout << "[" << e.first.first << ", " << e.first.last << "] = > " << e.second
         << '\n';
  }

  return 0;
}

/**
 *
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

struct Person {

        string name;
        int age;

        Person(string name_, int age_):name(name_)
                , age(age_) {}

        bool operator==(const Person& p) const {
                return (this->age == p.age && this->name == p.name);
        }

};

namespace std {
        template <>
        struct hash<Person> {
                size_t operator()(const Person &p) const {
                        return hash<string>()(p.name) ^ hash<int>()(p.age);
                }

        };
}

int main()
{
        unordered_map<Person, string>  uno_map;
        uno_map.emplace(Person("zoe", 23), "whuer");

        return 0;
}
 */

/**
 * #include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

struct Person {

	string name;
	int age;

	Person(string name_, int age_):name(name_)
		, age(age_) {}

};

struct hashGenerator {
	size_t operator()(const Person& p) const {
		return hash<string>()(p.name) ^ hash<int>()(p.age);
	}
};

struct personCmp {
	bool operator()(const Person& p,const Person& q) const {
		return (p->age == q.age && p->name == q.name);
	}
};

int main()
{
	unordered_map<Person, string, hashGenerator, per  sonCmp>  uno_map;
	uno_map.emplace(Person("zoe", 23), "whuer");

	return 0;
}
 * /