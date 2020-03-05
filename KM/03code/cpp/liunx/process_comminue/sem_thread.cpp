/*
 empty,full,同于同步
 mutex用于互斥
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#define BUFFERSIZE 10
#include "unpipc.h"
int buffer[BUFFERSIZE],bufferSize;
int inPointer,outPointer;
sem_t empty,full,mutex;
 
// 生产者线程函数
void *Producer(void *name) {
   for (int ith = 0; ith < 10; ith++) 
   {
	  sem_wait(&empty); //上来就阻塞为什么没，死锁 10
	  sem_wait(&mutex);// mutex用锁就没道理了吧。
      /**
	sem_wait() 
	decrements (locks) the semaphore pointed to by sem.  
	Ifthe semaphore's value is greater than zero, then the decrement
	proceeds, and the function returns, immediately. 

	If the semaphore
	currently has the value zero, then the call blocks until either it
	becomes possible to perform the decrement (i.e., the semaphore value
	rises above zero), or a signal handler interrupts the call.
    **/
	
	int data = rand() % 1000 + 1;
	  buffer[inPointer] = data;
	  printf("%s 在缓冲区%d 放入数据 %d\n",(char*)name, inPointer, data);
	  inPointer = (inPointer + 1) % bufferSize;
    
	  sem_post(&mutex);
	  sem_post(&full);
   }
}
 
// 消费者线程函数
void *Consumer(void *name) {
   for (int ith = 0; ith < 10; ith++) {
	  sem_wait(&full); //full 初始化为0，上来就阻塞这里。
	  sem_wait(&mutex);// full被激活后，Producer不停while出来，有可能继续写业务
 
	  int data = buffer[outPointer];
	  printf("   %s 在缓冲区%d 取出数据 %d\n",(char*)name, outPointer, data);
	  outPointer = (outPointer + 1) % bufferSize;
 
	  sem_post(&mutex);
	  sem_post(&empty);
   }
}
//g++ sem_thread.cpp -lrt  -lpthread
int main() {
   // 初始化缓冲区
   memset(buffer, -1, sizeof(buffer));
   bufferSize = 10;
   inPointer = outPointer = 0;
 
   // 初始化信号量
   //一般情况下，empty应该初始化为buffsize
   //但如果你想看到生产者，消费者“一放一取”地协同工作
   //你可以将empty初始化为1
   sem_init(&empty, 0, bufferSize);
   //sem_init(&empty, 0, 1);
   sem_init(&full, 0, 0);
   sem_init(&mutex, 0, 1);
 
   // 创建线程
   char proName[] = "生产者1号";
   char conName[] = "消费者1号";
   pthread_t proThread, conThread;
   int pt = pthread_create(&proThread, NULL, Producer, proName);
   int ct = pthread_create(&conThread, NULL, Consumer, conName);
   pthread_join(proThread, NULL);
   pthread_join(conThread, NULL);
 
   // 销毁信号量（释放资源）
   sem_destroy(&empty);
   sem_destroy(&full);
   sem_destroy(&mutex);
 
   return 0;
 
}