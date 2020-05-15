// out_of_range example
#include <iostream>       // std::cerr
#include <stdexcept>      // std::out_of_range
#include <vector>         // std::vector
#include <map>
using namespace std;
//g++ -std=c++11 map_test.cpp
int main (void) 
{
  std::vector<int> myvector(10); 
  //vector (size_type n)
  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  
  try 
  { 
     myvector[20]=100;
     myvector.at(20)=100;      // vector::at throws an out-of-range //区别1
  } 
  catch (const std::out_of_range& oor) 
  {
    std::cerr << "Out of Range error: " << oor.what() << '\n';

  }
  for (size_t i = 0; i < 20; i++)
  {
     myvector.push_back(i);
     std::cout << "size: " << (int) myvector.size() << " capacity: " << (int) myvector.capacity() << '\n';
     
  }

  myvector.clear();
  cout<<"--------------------"<<endl;
  std::cout << "size: " << (int) myvector.size() << " capacity: " << (int) myvector.capacity() << '\n';
   /////////////////////////////////////////////////////
  std::map<std::string,int> mymap = {
                { "alpha", 0 },
                { "beta", 0 }};

  mymap.at("alpha") = 10;
  mymap.at("beta") = 20;
  //mymap.at("gamma") = 30;
  mymap["gamma"] = 30; //区别1

  //If k does not match the key of any element in the container, 
  //the function throws an out_of_range exception.
  //terminate called after throwing an instance of 'std::out_of_range'
  //what():  map::at

  for (auto& x: mymap) {
    std::cout << x.first << ": " << x.second << '\n';
  }

  return 0;
}

  
