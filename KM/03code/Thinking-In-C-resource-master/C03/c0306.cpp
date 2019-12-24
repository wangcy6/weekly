#include <iostream>

using namespace std;


int    iDog, iCat, iBird, iFish;
char   cDog, cCat, cBird, cFish;
float  fDog, fCat, fBird, fFish;
double dDog, dCat, dBird, dFish;

static int static_i;
static int static_j;


void void_f(int ival)
{
cout<<"Pet id number(return void):"<<ival<<endl;
}
int int_f(int ival)
{
cout<<"Pet id number(return int):"<<ival<<endl;
return 0;
}

int main()
{
int    i_i, i_j ,i_k;
char   c_i, c_j, c_k;
double d_i, d_j, d_k;
//函数
cout<<"void f():     "<<(long)&void_f<<endl;
cout<<"int  f():     "<<(long)&int_f <<endl;
//静态变量
cout<<"static int_i: "<<(long)&static_i<<endl;
cout<<"static int_j: "<<(long)&static_j<<endl;

//全局变量 
cout<<"int iDog:     "<<(long)&iDog <<endl;
cout<<"int iCat:     "<<(long)&iCat <<endl;
cout<<"int iBird:    "<<(long)&iBird<<endl;
cout<<"int iFish:    "<<(long)&iFish<<endl;

cout<<"char cDog:    "<<(long)&cDog <<endl;
cout<<"char cCat:    "<<(long)&cCat <<endl;
cout<<"char cBird:   "<<(long)&cBird<<endl;
cout<<"char cFish:   "<<(long)&cFish<<endl;

cout<<"float fDog:   "<<(long)&fDog <<endl;
cout<<"float fCat:   "<<(long)&fCat <<endl;
cout<<"float fBird:  "<<(long)&fBird<<endl;
cout<<"float fFish:  "<<(long)&fFish<<endl;

cout<<"double fDog:  "<<(long)&dDog <<endl;
cout<<"double fCat:  "<<(long)&dCat <<endl;
cout<<"double fBird: "<<(long)&dBird<<endl;
cout<<"double fFish: "<<(long)&dFish<<endl;
//main函数内 局部变量 
cout<<"int i_i:     "<<(long)&i_i <<endl;
cout<<"int i_j:     "<<(long)&i_j <<endl;
cout<<"int i_k:     "<<(long)&i_k <<endl;

cout<<"char c_i:    "<<(long)&c_i <<endl;
cout<<"char c_j:    "<<(long)&c_j <<endl;
cout<<"char c_k:    "<<(long)&c_k <<endl;

cout<<"float f_i:   "<<(long)&d_i <<endl;
cout<<"float f_j:   "<<(long)&d_j <<endl;
cout<<"float f_k:   "<<(long)&d_k <<endl;


return 0;
}

