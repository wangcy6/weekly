#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myglobal;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

void print1()
{   int i=3;
	while(i-->0)
	{
		  printf("1");
          fflush(stdout);
          sleep(1);
	}
}
void print2()
{   
    int i=3;
	while(i-->0)
	{
		  printf("2");
          fflush(stdout);
          sleep(1);
	}
}

void print2()
{   
    int i=3;
	while(i-->0)
	{
		  printf("2");
          fflush(stdout);
          sleep(1);
	}
}

void print3()
{   
    int i=10;
	while(i-->0)
	{
		  printf(".");
          fflush(stdout);
          sleep(1);
	}
}

void *thread_function(void *arg)
{
     int i,j;
     for ( i=0; i<20; i++)
     {
          pthread_mutex_lock(&mymutex);
          j=myglobal; j=j+1;
          printf(".");
          fflush(stdout);
          sleep(1);
          myglobal=j;
          pthread_mutex_unlock(&mymutex);
     }
     return NULL;
}
//g++ print_thread.cpp -lpthread
int main(void) {
  int number =2;
  pthread_t mythread[number];
  for (int k = 0; k < number; k++)
  {
      if ( pthread_create( &mythread[k], NULL, thread_function, &mythread[k]) ) 
      {
        printf("error creating thread.");
        abort();
     }
  }
  pthread_t mythread[3];
  pthread_create( &mythread[0], NULL, print1, NULL)
  pthread_create( &mythread[1], NULL, print2, NULL)
  pthread_create( &mythread[2], NULL, print3, NULL)


  for(int i=0;i<3;i++)
  {
	  pthread_join(&mythread[i],NULL);
  }

  
  sleep(100);
  printf("\nmyglobal equals %d\n",myglobal);
  exit(0);
}