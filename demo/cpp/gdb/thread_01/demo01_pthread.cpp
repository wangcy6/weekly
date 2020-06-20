#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
#include <typeinfo>
#include <unistd.h>
using namespace std;

pthread_t tid[2];
//测试case1 进程exit()，全部线程退出
//测试case2 进程pthread_exit，剩余线程继续运行
void* test_func1(void *arg)
{  
    pthread_t id = pthread_self();
    pthread_detach(id);
    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
    }

    for(int i=0;i<5500;i++)
    {
        printf("thread =%ld,is surviveing , and is speaking from the detached thread...=%d\n",id,i);
        
    }
	sleep(3);
	
    return NULL;
}

////g++  -pthread demo01_pthread.cpp
int main(void)
{   
    
    for(int i=0;i<2;i++)
    {
       pthread_create(&(tid[i]), NULL, &test_func1, NULL);
      
    }

     sleep(5);
	 pthread_t id = pthread_self();
	 printf("Main thread dying before pthread_exit =%ld...\n",id);
	 pthread_exit(NULL); /* process continues until last  
                                threads termintates */
	 

}
