// out_of_range example
#include <iostream>       // std::cerr
#include <stdexcept>      // std::out_of_range
#include <vector>         // std::vector
#include <map>
using namespace std;
int main (void) 
{
  std::vector<int> myvector(10); 
  try 
  {
    myvector.at(20)=100;      // vector::at throws an out-of-range
  }
  catch (const std::out_of_range& oor) 
  {
    std::cerr << "Out of Range error: " << oor.what() << '\n';

    // Strong guarantee: if an exception is thrown, there are no changes in the container.
    // It throws out_of_range if n is out of bounds.
  }


  std::map<std::string,int> mymap = {
                { "alpha", 0 },
                { "beta", 0 }};

  mymap.at("alpha") = 10;
  mymap.at("beta") = 20;
  mymap.at("gamma") = 30;//If k does not match the key of any element in the container, the function throws an out_of_range exception.

  for (auto& x: mymap) {
    std::cout << x.first << ": " << x.second << '\n';
  }

  return 0;
}

  return 0;
}