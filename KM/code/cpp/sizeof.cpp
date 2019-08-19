#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct{
  char  c1;// 1 2 
  short s; // 2 2
  char  c2; //1 2 
  int   i;//4   4 
  } struct1;

//return 1 : little-endian 0x 10
//       0 : big-endian 0x 01
int checkCPUendian()
{
    union {
        unsigned int a;
        unsigned char b; 
    } c;
  
    c.a = 1;//0x 01
    return (c.b == 1); 
}
int main(int argc, char* argv[])
{ 
  //getconf LONG_BIT 64
  cout <<"int=" <<sizeof(int)<<endl;//4
  cout <<"long=" <<sizeof(long)<<endl;//8
  cout<< "struct1=" <<sizeof(struct1)<<endl;//12
  return 0;

}