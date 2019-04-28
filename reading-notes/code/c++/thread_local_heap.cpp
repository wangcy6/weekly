#include<pthread.h>
#include<unistd.h>
#include<iostream>
#include<syscall.h>
#include<string.h>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * foo(void *pBuffer)
{
   pthread_mutex_lock(&mutex);
   strcpy((char*)pBuffer,"hello");//主线程的堆数据在此被修改
   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&cond);

}
//g++  thread_local_heap.cpp  -lpthread 
int main(int n, char *arg[])
{
   char *Buffer = new char[20]; //主线程的堆数据
   strcpy((char*)Buffer,"aabcd");
   pthread_t pthread_id1;
   pthread_create(&pthread_id1,NULL,foo,(void *)Buffer);
   pthread_mutex_lock(&mutex);
   pthread_cond_wait(&cond,&mutex);//注意pthread_cond_wait()的使用方法
   pthread_mutex_unlock(&mutex);
   cout<<Buffer<<endl;// 输出数据Buffer到标准输出
   return 0;
}
