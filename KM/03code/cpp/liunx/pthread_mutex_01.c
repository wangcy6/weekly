#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myglobal;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) 
 {
  int* who =(int*)arg;
  int i,j;
  for ( i=0; i<20; i++) 
  {
    //https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_lock.html
    if (pthread_mutex_lock(&mymutex) >0)
    {
    
    }else
    {
    }
    
    
    j=myglobal;
    j=j+1;

    printf("%d",*who);
    fflush(stdout);
    sleep(1);
    myglobal=j;
    pthread_mutex_unlock(&mymutex);
    //the scheduling policy shall determine which thread shall acquire the mutex.
  }
  return NULL;
}
//g++ pthread_mutex_01.c -lpthread
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