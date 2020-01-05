#include <stdio.h>
#include <memory>
#include <pthread.h>
using namespace std;

/**
 * 1 同一个shared_ptr被多个线程“读”是安全的。

2 同一个shared_ptr被多个线程“写”是不安全的。

3 共享引用计数的不同的shared_ptr被多个线程”写“ 是安全的。
 **/ 
shared_ptr<int> gp(new int(2000));

shared_ptr<int>  CostaSwapSharedPtr1(shared_ptr<int> & p)
{
    shared_ptr<int> p1(p);
    shared_ptr<int> p2(new int(1000));
    p1.swap(p2);
    p2.swap(p1);
    return p1;
}

shared_ptr<int>  CostaSwapSharedPtr2(shared_ptr<int> & p)
{
    shared_ptr<int> p2(new int(1000));
    p.swap(p2);
    p2.swap(p);
    return p;
}


void* thread_start(void * arg)
{
    int i =0;
    for(;i<100000;i++)
    {
        shared_ptr<int> p= CostaSwapSharedPtr2(gp);
        if(*p!=2000)
        {
            printf("Thread error. *gp=%d \n", *gp);
            break;
        }
    }
    printf("Thread quit \n");
    return 0;
}


//g++ -std=c++11 -g shared_ptr_safe.cpp  -pthread
int main()
{
    pthread_t thread;
    int thread_num = 10, i=0;
    
    pthread_t* threads = new pthread_t[thread_num];
    for(;i<thread_num;i++)
        pthread_create(&threads[i], 0 , thread_start , &i);
    
    
    for(i=0;i<thread_num;i++)
        pthread_join(threads[i],0);
    delete[] threads;
    return 0;
}