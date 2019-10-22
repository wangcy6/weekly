#include<stdio.h>
#include <unistd.h>
#include <iostream>
// 必须的头文件
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS 3
 
// 线程的运行函数
void* say_hello(void* args)
{
    cout << "Hello Runoob！" << endl;
	sleep(60*60);
    return 0;
}
// g++ 01_pthread.cpp -lpthread -o test
int main()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    sleep(60*60);
	pthread_exit(NULL);

}