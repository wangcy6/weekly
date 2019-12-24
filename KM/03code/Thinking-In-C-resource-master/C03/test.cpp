#include <iostream>

int interbyteNum   = 0;
int decimalbyteNum = 0;
void _rev(unsigned char* s)
{
unsigned char* p = s;
unsigned char* q = s;
unsigned char temp;
while('\0' != *(++q + 1));
while(p < q)
{
if(*p != *q)
{
temp = *p;
*p = *q;
*q = temp;
}
++p;
--q;
}
}

unsigned char* DtoA(int n)
{
unsigned char* byte = new unsigned char[65];
int sign = n; 
if(sign < 0)
n = -n;
int i = 0;
do
{
byte[i++] = n % 2 + '0';
n /= 2;
}while(n > 0);
if(sign < 0)
byte[i++] = '-';
byte[i] = '\0';
_rev(byte);
return byte;
}

char* itoa(int value,char* string, int radix)
{
char tmp[65];
char *tp = tmp;
int i;
unsigned v;
int sign;
char* sp;

if(radix > 36 || radix <= 1)
{
std::cout<<"Wrong Radix"<<std::endl;
return 0;
}

sign = (value < 0);
if(sign)
v = static_cast<unsigned>(-value);
else
v = static_cast<unsigned>(value);

while(v || tp == tmp)
{
i = v % radix;
v /= radix;
if(i < 10)
*tp++ = i + '0';
else
*tp++ = i + 'A' - 10;
}
interbyteNum =(int)(tp - tmp) - 1;
if(string == NULL)
string = static_cast<char*>(new char[(tp - tmp) + sign + 1]);
sp = string;
//if(sign)
//*sp++ = '-';

while(tp > tmp)
*sp++ = *--tp;
*sp = 0;
return string;
}

char* dtoa(double value,char* string)
{
char Decimal[65];
char* ptr = Decimal;
unsigned v;
int sign;

sign = (value < 0);
if(sign)
value = -value;
int flag = 1;
while(value - (int)(value) != 0.0)
{
*ptr++ = (unsigned char)(int)(value*=2) + '0';
if(flag && *(ptr-1) == '1')
{
flag = 0;
decimalbyteNum = ptr - Decimal - 1;
}
double k = (value - (int)(value));
value = k;
}

if(string == NULL)
string = static_cast<char*>(new char[(ptr - Decimal) + 1]);
char* sp = string;

char* start = Decimal;
*sp++ = '.';
while(ptr > start)
*sp++ = *start++;
*sp = 0;
return string;
}

int main()
{
double dVal = 0.0000546;

char BYTE[64] = {'0'};
int exponentBit = 0;
if(dVal < 0.0)
{
BYTE[0] = '1';//1代表负
dVal = -dVal;
}
else
BYTE[0] = '0';//0代表正



int iVal = static_cast<int>(dVal);
double decimal  = dVal - iVal;

std::cout<<iVal<<std::endl;
std::cout<<decimal<<std::endl;

char iArray[64] = {'0'};
itoa(iVal, iArray,2);
std::cout<<iArray<<std::endl;

char dArray[64] = {'0'};
dtoa(decimal,dArray);
std::cout<<iArray<<dArray<<std::endl;

if(sizeof(dVal) == sizeof(double))//判断是单精度还是双精度
{
std::cout<<"Double"<<std::endl;
exponentBit = 11;
}
else
{
std::cout<<"float"<<std::endl;
exponentBit = 7;
}
std::cout<<interbyteNum<<std::endl;
std::cout<<decimalbyteNum<<std::endl;

if(dVal > 1.000000000)
{
std::cout<<"dVal > 1"<<std::endl;
itoa(interbyteNum + ((sizeof(dVal) == sizeof(float)) ? 1023 : 127),&BYTE[1],2);
std::cout<<BYTE<<std::endl;
}
else
{
std::cout<<"dVal < 1"<<std::endl;
itoa(decimalbyteNum + ((sizeof(dVal) == sizeof(float)) ? -1023 : -127),&BYTE[1],2);
std::cout<<BYTE<<std::endl;
}return 0;
}
