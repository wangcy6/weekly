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

// 如果不好理解，借助java  你非常清楚了 
class node;
class Node {
public:
  int a;
  int b;
  int c;
  Node() {}
  Node(vector<int> v) {
    sort(v.begin(), v.end());
    a = v[0];
    b = v[1];
    c = v[2];
  }

  bool operator==(Node i) {
    if (i.a == this->a && i.b == this->b && i.c == this->c) {
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  unordered_map<Node, int> m;

  vector<int> v;
  v.push_back(3);
  v.push_back(8);
  v.push_back(9);
  Node n(v);

  m[n] = 0;

  return 0;
}
/**
 * To be able to use std::unordered_map (or one of the other unordered
associative containers) with a user-defined key-type, you need to define two
things:

A hash function; this must be a class that overrides operator() and calculates
the hash value given an object of the key-type. One particularly
straight-forward way of doing this is to specialize the std::hash template for
your key-type.

A comparison function for equality; this is required because the hash cannot
rely on the fact that the hash function will always provide a unique hash value
for every distinct key (i.e., it needs to be able to deal with collisions), so
it needs a way to compare two given keys for an exact match. You can implement
this either as a class that overrides operator(), or as a specialization of
std::equal, or – easiest of all – by overloading operator==() for your key type (as
 you did already)

 如果不好理解，借助java 你非常清楚了
 https://www.baeldung.com/java-hashcode
 public class User {

    private long id;
    private String name;
    private String email;

    // standard getters/setters/constructors

    @Override
    public int hashCode() {
        return 1;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null) return false;
        if (this.getClass() != o.getClass()) return false;
        User user = (User) o;
        return id == user.id
          && (name.equals(user.name)
          && email.equals(user.email));
    }

    // getters and setters here
@Override
public int hashCode() {
    int hash = 7;
    hash = 31 * hash + (int) id;
    hash = 31 * hash + (name == null ? 0 : name.hashCode());
    hash = 31 * hash + (email == null ? 0 : email.hashCode());
    return hash;
}
}
 **/
