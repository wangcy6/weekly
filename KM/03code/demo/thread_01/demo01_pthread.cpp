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

    for(int i=0;i<15;i++)
    {
        printf("thread =%ld,is surviveing , and is speaking from the detached thread...=%d\n",id,i);
        sleep(1);
    }
	
    return NULL;
}
//测试case 进程正常推出，执行回调
void atexit_normal()
{   

     cout<<"I am killed"<<endl;
	 printf("pid=%d\n", getpid());
}
////g++  -pthread demo01_pthread.cpp
int main(void)
{   
    //进程离开时候清理数据
    atexit(atexit_normal);
    int err;
    //创建线程
    for(int i=0;i<2;i++)
    {
        err = pthread_create(&(tid[i]), NULL, &test_func1, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");
    }

     sleep(5);
	 pthread_t id = pthread_self();
	 printf("Main thread dying before pthread_exit =%ld...\n",id);
	 pthread_exit(NULL); /* process continues until last  
                                threads termintates */
	 
	 //printf("Main thread dying after pthread_exit =%ld...\n",id);
    // return 0;  后面代码用不到了可以直接屏蔽
}

/**
线程正常终止的方法：

1、return从线程函数返回。 
   //exit(EXIT_SUCCESS) return会被自动优化成exit，主函数中使用return会退出所有线程的运行

2、通过调用函数pthread_exit使线程退出
    //To allow other threads to continue execution, the main thread should
     //terminate by calling pthread_exit() rather than exit(3).
3. 线程可以被同一进程中的其他线程取消。
    pthread_canel
**/