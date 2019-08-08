#include<stdio.h>  
#include<pthread.h>  
#include<string.h>  
#include<sys/types.h>  
#include<unistd.h>
#include <string>
#include <iostream>
using namespace std;

int main()  
{  
    pid_t pid1;
	pid_t pid2;
    pid1=fork();
	pid2=fork();
	cout<<"pid1="<<pid1<< "pid2"<<pid2<<endl;
    return 0;  
}  