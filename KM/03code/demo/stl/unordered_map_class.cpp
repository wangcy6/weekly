#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;


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
typedef std::unordered_map<Person,int,MyHashFunction> myHashMap; //忘记了MyHashFunction报错
typedef myHashMap::iterator  myiterator;

int main() {

        myHashMap mymap;
        //测试自定义类
        mymap.rehash(20);

        //key 
        Person p1("kartik", "kapoor");
        Person p2("Ram", "Singh");
        Person p3("Laxman", "Prasad");
       //value
        std::pair <Person,int> item1= make_pair(p1,199);
        std::pair <Person,int> item2= make_pair(p2,299);
        std::pair <Person,int> item3= make_pair(p3,199);
        

        //01 测试key插入 
        //http://www.cplusplus.com/reference/unordered_map/unordered_map/operator[]/
        //http://www.cplusplus.com/reference/unordered_map/unordered_map/insert/
        mymap[p1] = 100;
        pair<myiterator,bool> result1=mymap.insert(item1);  //元素重复,不修改返回false
        if(result1.second ==true)
        {
                cout<< p1.first<< "successfully inserted" <<endl;
        }else
        {
              cout<< p1.first<< " repeated " <<endl;
        }
         

       pair<myiterator,bool> result2= mymap.insert(item2); 
       if(result2.second ==true)
        {
                cout<< p2.first<< "successfully inserted" <<endl;
        }else
        {
              cout<< p2.first<< " repeated " <<endl;
        } 
        mymap[p2] =200;  //元素重复,修改  reference 

        mymap[p3] = 400; //new element inserted
        mymap[p3] = 500; //existing element accessed


        std::cout << "-------test::same key insert ----------"<<endl;
        for (auto e : mymap) {
        cout << "[" << e.first.first << ", " << e.first.last << "] = > " << e.second
                << '\n';
        }

        //02 测试自定义类 hash eqal
         std::cout << "------ test::hash_function  && key_eq---------"<<endl;
         //http://www.cplusplus.com/reference/unordered_map/unordered_map/hash_function/
         myHashMap::hasher fn = mymap.hash_function();
         std::cout << "hash_function(p1): " << fn (p1) << std::endl;
         std::cout << "hash_function(p2): " << fn (p2) << std::endl;
         std::cout << "hash_function(p3): " << fn (p3) << std::endl;

      
        //http://www.cplusplus.com/reference/unordered_map/unordered_map/key_eq/
        std::cout << "mymap.key_eq() is p1 == p3 " <<mymap.key_eq()(p1,p3)<< std::endl;
        std::cout << "mymap.key_eq() is p1 == p1 " <<mymap.key_eq()(p1,p1)<< std::endl;

        

        //03 测试指标
        std::cout << "----------size ----------"<<endl;
        std::cout << "current size: " << mymap.size() << std::endl;
        std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;
        std::cout << "current load_factor: " << mymap.load_factor() << std::endl;
        std::cout << "current max_load_factor: " << mymap.max_load_factor() << std::endl;




  return 0;
}
