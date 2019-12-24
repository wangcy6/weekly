#include <iostream>

using namespace std;
int main()
{

cout <<"A  = X + Y  - 2/2 + Z"<<endl;
cout<<"Pleas input X , Y and Z："<<endl;
int X, Y, Z;
cin>>X>>Y>>Z;
cout << "A = "<< X + Y - 2/2 + Z<<endl;

cout <<"A  = X + (Y  - 2)/(2 + Z)"<<endl;
cout << "A = "<< X + (Y - 2)/(2 + Z)<<endl;

return 0;
}



