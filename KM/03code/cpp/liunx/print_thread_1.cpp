#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;
static volatile int myglobal = 0;
int g_count = 10;//打印多少遍，线程退出

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
//思路1  
//线程A打印1 ，
//线程B 打印21 
//线程C打印。 
//输出：
//121.121..121...121....121.....121......

void* print1(void *arg)
{   
    
    int i=g_count;
	while(i-->0)
	{   
        //cout<<"myglobal1 ="<<myglobal<<endl;
		pthread_mutex_lock(&mutex);
		if(myglobal%3 ==0)
		{
			
		}else
		{
			
			pthread_cond_wait(&cond3,&mutex);
		}
		myglobal++;
		printf("1");
		fflush(stdout);
		sleep(1);
		
		pthread_cond_signal(&cond1);
		
	
		pthread_mutex_unlock(&mutex);
		
	}
}
void* print2(void *arg)
{   
    int i=g_count;
	while(i-->0)
	{   
        
		pthread_mutex_lock(&mutex);
		
		if(myglobal%3 ==1)
		{
			
		}else
		{
			pthread_cond_wait(&cond1,&mutex);
		}
		
		
		myglobal++;
		
		printf("21");
		fflush(stdout);
		sleep(1);
		
		pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&mutex);
		
		
		
	}
}

void* print3(void *arg)
{   
   
    int i=g_count;
	while(i-->0)
	{   
       
		pthread_mutex_lock(&mutex);
		//0 1 2 ,3 4 5, 6,7,8
		if(myglobal%3 ==2)
		{
			
		}else
		{
			pthread_cond_wait(&cond2,&mutex);
		}
		
		int counts =myglobal/3+1;
		
		for(int i=0;i<counts;i++)
		{
		  printf(".");
		  fflush(stdout);		 
		}
		sleep(1);
		
		myglobal++;
	
       
		pthread_cond_signal(&cond3);
		pthread_mutex_unlock(&mutex);
		
	}
}


//g++ print_thread.cpp -g -lpthread
int main(void) 
{  

  myglobal =0;
  pthread_t mythread[3];
  pthread_create(&mythread[0], NULL, print1, NULL);
  pthread_create(&mythread[1], NULL, print2, NULL);
  pthread_create(&mythread[2], NULL, print3, NULL);


  for(int i=0;i<3;i++)
  {
	  pthread_join(mythread[i],NULL);
  }


 
  return 0;
}