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
//https://www.sczyh30.com/posts/C-C/cpp-stl-hashmap/
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
//因此如果想在 unordered_map 中使用自定义的类，则必须为此类提供一个哈希函数和一个判断对象是否相等的函数
//Object 类里有两个重要方法：hashCode 和 equals 方法
class MyHashFunction {
public:
  // Use sum of lengths of first and last names
  // as hash function.
  size_t operator()(const Person &p) const {
    return p.first.length() + p.last.length();
  }
};

// g++ -std=c++11 unordered_map_class.cpp
typedef std::unordered_map<Person,int> myHashMap;

int main() {

        myHashMap mymap;
        //测试自定义类
        //key_eq
        mymap.rehash(20);
        Person p1("kartik", "kapoor");
        Person p2("Ram", "Singh");
        Person p3("Laxman", "Prasad");

        std::pair <Person,int> item1= make_pair(p1,199);
        std::pair <Person,int> item2= make_pair(p2,299);
        std::pair <Person,int> item3= make_pair(p3,199);
        

        //01 测试插入 

        mymap[p1] = 100;
        mymap.insert(item1);  // 重复元素不修改

        mymap.insert(item2); 
        mymap[p2] =200;  //重复元素修改

        mymap[p3] = 400;
        mymap[p3] = 400; //unordered_map 不允许重复,



        std::cout << "----------ouput----------"<<endl;
        for (auto e : mymap) {
        cout << "[" << e.first.first << ", " << e.first.last << "] = > " << e.second
                << '\n';
        }
        //02 测试自定义类
         std::cout << "----------calss hash function object---------"<<endl;
        //  myHashMap::hasher fn = mymap.hash_function();
        //  std::cout << "hash(p1): " << fn (p1) << std::endl;
        //  std::cout << "hash(p2): " << fn (p2) << std::endl;
        
        //03 测试指标
        std::cout << "----------size ----------"<<endl;
        std::cout << "current size: " << mymap.size() << std::endl;
        std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;
        std::cout << "current load_factor: " << mymap.load_factor() << std::endl;
        std::cout << "current max_load_factor: " << mymap.max_load_factor() << std::endl;




  return 0;
}
