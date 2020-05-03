#include <iostream>

using namespace std;
int main()
{
int i;
cout<<"type a number and 'Enter'"<<endl;
cin >> i;

cout<<(i != 5 ? (i > 5 ? "i > 5": "i < 5"):"i == 5")<<endl;

return 0;
}
