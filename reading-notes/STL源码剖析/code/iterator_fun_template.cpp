#include<iostream>  
using namespace std;  
template<typename T1, typename T2>  
int get_max_type(T1 a, T2 b)  
{  
    int nMax = 0;  
    if (sizeof(T1) >= sizeof(T2))  
    {  
        nMax = sizeof(T1);  
    }  
    else  
    {  
        nMax = sizeof(T2);  
    }  
  
    return nMax;  
}  
int main(int argc, char * argv[])  
{  
    int nMax = get_max_type(‘a’, 10);  
    cout<<”max:”<<nMax<<endl;  
    return 0;  
}  