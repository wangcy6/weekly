#include <iostream>
#include <string>
using namespace std; 
int main ()
{
  std::string str ("Test string");
  std::string* ptr=&str;                                                                                                                                             
  cout<<"ptr="<<ptr<<"*ptr="<<*ptr<<endl;       
  cout<<ptr->at(2)<<endl;  
  //cout <<*(ptr+1)<<endl; core  字符串指针     
  string* str = {"hello", "world"}; 
  //char *str[] = {"Hello", "C++", "World"}; //char (*str)[] = （字符串）指针数组
  for (int i=0; i<str.length(); ++i)
  {
    std::cout << str[i];
  }
  return 0;
}