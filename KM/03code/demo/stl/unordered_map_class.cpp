#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

struct Person
{
  string first, last; // First and last names

  Person(string f, string l)
  {
    first = f;
    last = l;
  }
  bool operator==(const Person &p) const
  {
    return first == p.first && last == p.last;
  }
  friend ostream &operator<<(ostream &os, const Person &person)
  {
    os << "[" << person.first << ", " << person.last << "] = > " << endl;
    return os;
  }
};
//因此如果想在 unordered_map 中使用自定义的类，则必须为此类提供一个哈希函数和一个判断对象是否相等的函数
//Object 类里有两个重要方法：hashCode 和 equals 方法
class MyHashFunction
{
public:
  // Use sum of lengths of first and last names
  // as hash function.
  size_t operator()(const Person &p) const
  {
    return p.first.length() + p.last.length();
  }
};
namespace std
{
  template <>
  struct hash<Person>
  {
    size_t operator()(const Person &p) const
    {
       return p.first.length() + p.last.length();
    }
  };
} // namespace std
//https://en.wikipedia.org/wiki/Partial_template_specialization
//http://www.gotw.ca/publications/mill17.htm

// g++ -std=c++11 unordered_map_class.cpp
typedef std::unordered_map<Person, int> myHashMap; //忘记了MyHashFunction报错
typedef myHashMap::iterator myiterator;

int main()
{

  myHashMap mymap;
  //测试自定义类
  mymap.rehash(20);

  //key
  Person p1("a", "d");
  Person p2("b", "e");
  Person p3("c", "f");
  //value
  std::pair<Person, int> item1 = make_pair(p1, 199);
  std::pair<Person, int> item2 = make_pair(p2, 299);
  std::pair<Person, int> item3 = make_pair(p3, 199);

  //01 测试key插入
  //http://www.cplusplus.com/reference/unordered_map/unordered_map/operator[]/
  //http://www.cplusplus.com/reference/unordered_map/unordered_map/insert/
  mymap[p1] = 100;
  pair<myiterator, bool> result1 = mymap.insert(item1); //元素重复,不修改返回false
  if (result1.second == true)
  {
    cout << p1.first << "successfully inserted" << endl;
  }
  else
  {
    cout << p1.first << " repeated " << endl;
  }

  pair<myiterator, bool> result2 = mymap.insert(item2);
  if (result2.second == true)
  {
    cout << p2.first << "successfully inserted" << endl;
  }
  else
  {
    cout << p2.first << " repeated " << endl;
  }
  mymap[p2] = 200; //元素重复,修改  reference

  mymap[p3] = 400; //new element inserted
  mymap[p3] = 500; //existing element accessed

  std::cout << "-------test::same key insert ----------" << endl;
  for (auto e : mymap)
  {
    cout << "[" << e.first.first << ", " << e.first.last << "] = > " << e.second
         << '\n';
  }

  //02 测试自定义类 hash eqal
  std::cout << "------ test::hash_function  && key_eq---------" << endl;
  //http://www.cplusplus.com/reference/unordered_map/unordered_map/hash_function/
  myHashMap::hasher fn = mymap.hash_function();
  std::cout << "hash_function(p1): " << fn(p1) << std::endl;
  std::cout << "hash_function(p2): " << fn(p2) << std::endl;
  std::cout << "hash_function(p3): " << fn(p3) << std::endl;

  //http://www.cplusplus.com/reference/unordered_map/unordered_map/key_eq/
  std::cout << "mymap.key_eq() is p1 == p3 " << mymap.key_eq()(p1, p3) << std::endl;
  std::cout << "mymap.key_eq() is p1 == p1 " << mymap.key_eq()(p1, p1) << std::endl;

  //03 测试指标
  std::cout << "---------03 bucket ----------" << endl;
  std::cout << "current size: " << mymap.size() << std::endl;
  std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;
  std::cout << "current load_factor: " << mymap.load_factor() << std::endl;
  std::cout << "current max_load_factor: " << mymap.max_load_factor() << std::endl;

  for (int i = 0; i < mymap.bucket_count(); ++i)
  {
     std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
  }

  //03 http://www.cplusplus.com/reference/unordered_map/unordered_map/erase/
  //http://www.cplusplus.com/reference/map/map/erase/
  //https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys
  std::cout << "----------04 erase ----------" << endl;

  std::unordered_map<Person, int>::const_iterator got = mymap.find(p1);
  if (got == mymap.end())
    std::cout << "not found";
  else
    std::cout << got->first << "= > " << got->second << endl;
   mymap.erase(got);
  //myiterator its = mymap.erase(got);
  // std::cout << its->first << " = > " << its->second << endl; //Segmentation fault (core dumped)

  return 0;
}

/**
 * .[root@vm-10-115-37-60 stl]# ./a.out 
a repeated 
bsuccessfully inserted
-------test::same key insert ----------
[c, f] = > 500
[b, e] = > 200
[a, d] = > 100
------ test::hash_function  && key_eq---------
hash_function(p1): 2
hash_function(p2): 2
hash_function(p3): 2
mymap.key_eq() is p1 == p3 0
mymap.key_eq() is p1 == p1 1
----------size ----------
current size: 3
current bucket_count: 23
current load_factor: 0.130435
current max_load_factor: 1
bucket #0 has 0 elements.
bucket #1 has 0 elements.
bucket #2 has 3 elements.
bucket #3 has 0 elements.
bucket #4 has 0 elements.
bucket #5 has 0 elements.
bucket #6 has 0 elements.
bucket #7 has 0 elements.
bucket #8 has 0 elements.
bucket #9 has 0 elements.
bucket #10 has 0 elements.
bucket #11 has 0 elements.
bucket #12 has 0 elements.
bucket #13 has 0 elements.
bucket #14 has 0 elements.
bucket #15 has 0 elements.
bucket #16 has 0 elements.
bucket #17 has 0 elements.
bucket #18 has 0 elements.
bucket #19 has 0 elements.
bucket #20 has 0 elements.
bucket #21 has 0 elements.
bucket #22 has 0 elements.
----------04 erase ----------
[a, d] = > 
= > 100
Segmentation fault (core dumped)
 */