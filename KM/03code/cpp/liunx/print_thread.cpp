#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;
static volatile int myglobal = 0;
static volatile bool flag = false;
int g_count = 10;//打印多少遍，线程退出

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; //  
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER; // 
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;//
  

 //输出：121.121..121...
//简化1 121. 121. 121.121. 
///          1234 5 6 78 9 
//输出：121.121..121...
//1---->2 2 6 10 thead2
//1---->. 4 8 12 thead3
//2---->1,5,9  thead1
//.----->1 5 9 threa1
//   1 -->2 -->1 
//   1 ——3 ————1 
   
//1 wait: 2 4 6 8 10 12 14


void* print1(void *arg)
{   
    
    int i=g_count;
	while(i-->0)
	{   
        //cout<<"myglobal1 ="<<myglobal<<endl;
		pthread_mutex_lock(&mutex);
		
		//if(myglobal >0 && myglobal/4 ==0)
		if(myglobal >0 && flag ==false)
		{  
			pthread_cond_wait(&cond2,&mutex);//等待线程2
		}else if(myglobal >0 && flag ==true)
		{
			myglobal =2;
			pthread_cond_wait(&cond3,&mutex);//等待线程3
		}else
		{
			 myglobal =1;
		}			
		
		//myglobal++;
		printf("1");
		fflush(stdout);
		sleep(1);
		myglobal =1;
		if(flag =false)
		{    
	        flag =true;
			
			pthread_cond_signal(&cond1);
		}else
		{   
	        flag =false;
			
	      	pthread_cond_signal(&cond3);		
		}
		
	
	
		pthread_mutex_unlock(&mutex);
		
	}
}
void* print2(void *arg)
{   
    int i=g_count;
	while(i-->0)
	{   
        
		pthread_mutex_lock(&mutex);
		
		//条件是什么
		if(myglobal !=1 )
		{
			
		}else
		{    //条件不满足
		    pthread_cond_wait(&cond1,&mutex);//等待线程1	
		}
	  
		
	   
		
		
		myglobal =1;
		
		printf("2");
		fflush(stdout);
		sleep(1);
		
		pthread_cond_signal(&cond3);
		pthread_mutex_unlock(&mutex);
		
		
		
	}
}

void* print3(void *arg)
{   
   
    int i=g_count;
	while(i-->0)
	{   
       
		pthread_mutex_lock(&mutex);
		//条件是什么
		pthread_cond_wait(&cond2,&mutex);
		
		
		//int counts =myglobal/3+1;
		
		//for(int i=0;i<counts;i++)
		//{
		  printf(".");
		  fflush(stdout);		 
		//}
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