#include <iostream>

using namespace std;

enum Color
{
blue    = 1,
red     = 2,
black   = 3,
white   = 4,
yellow  = 5,
};


int main()
{

Color mcolor = blue;

for(int i = blue ; i <= yellow; i++)
{
switch(i)
{
case blue:
cout<<"blue color is:   "<<blue<<endl;
break;
case red:
cout<<"red color is:    "<<red<<endl;
break;
case black:
cout<<"black color is:  "<<black<<endl;
break;
case white:
cout<<"white color is:  "<<white<<endl;
break;
case yellow:
cout<<"yellow color is: "<<yellow<<endl;
break;
}
}


return 0;
}
