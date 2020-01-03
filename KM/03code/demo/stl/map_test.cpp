//https://www.cnblogs.com/blueoverflow/p/4923523.html

// erasing from map
#include <iostream>
#include <map>

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=60;
  mymap['f']=60;



  // show content:
  for (it=mymap.begin(); it!=mymap.end(); )
 { 
    

     if (it->second == 60)
     {
          mymap.erase(it++);
          std::cout << it->first << " => " << it->second << '\n';
     }else
     {   
         std::cout << it->first << " => " << it->second << '\n';
         ++it;
     }
     
   }  


  return 0;
}