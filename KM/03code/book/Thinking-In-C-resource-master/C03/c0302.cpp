#include <iostream>

void find(int ival)
{
for(int i = 2; i <= ival; i++){
bool flag = true;
for(int j = 2; j < i; j++){
if(i % j == 0){
flag = false;
break;
}
}
if(flag )
std::cout<<i<<std::endl;
}
}

int main()
{
int input;
std::cout<<"Please input a number:";
std::cin>>input;

find(input);

return 0;

}
