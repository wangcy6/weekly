#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myglobal;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

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
  

  for ( int i=0; i<20; i++) 
  {
    pthread_mutex_lock(&mymutex);
    myglobal=myglobal+1;
    pthread_mutex_unlock(&mymutex);
    printf("o");
    fflush(stdout);
    sleep(1);
  }
   sleep(100);
  printf("\nmyglobal equals %d\n",myglobal);
  exit(0);
}