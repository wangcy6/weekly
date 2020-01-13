
/*********************************************************************
		C-DAC Tech Workshop : hyPACK-2013
                           October 15-18, 2013

 Example      : pthread-readwrite-lock-demo.c
   
 Objective    : Code to demonstrate read-write lock APIs for Demo Purpose.
  
 Description  : Demo code to illustrate different read-write locks APIs. 

 Input        : None

 Output	      : Sequence of acquiring and releasing read-write lock.

 Created      : August-2013

 E-mail       : hpcfte@cdac.in     
       
********************************************************************/

#define _MULTI_THREADED
#include <pthread.h> // header file inclusion
#include <stdio.h>
#include <unistd.h>

pthread_rwlock_t rwlock;

void *rdlockThread(void *arg) // illustrate readlock APIs
{
  int rc;

  printf("\n\nEntered thread1, getting read lock\n\n");
  rc = pthread_rwlock_rdlock(&rwlock);

  printf("\ngot the rwlock read lock\n");

  sleep(5); // put some wait time here

  printf("\nunlock the read lock\n");
  rc = pthread_rwlock_unlock(&rwlock);

  return NULL;
}

void *wrlockThread(void *arg) // illustrate writelock APIs
{
  int rc;

  printf("\n\nEntered thread2, getting write lock\n\n");
  rc = pthread_rwlock_wrlock(&rwlock);
  

  printf("\nGot the rwlock write lock, now unlock\n\n");
  rc = pthread_rwlock_unlock(&rwlock);

  return NULL;
}
//g++  pthread_rwlock_01.cpp -lpthread
int main(int argc, char **argv)
{
  int rc = 0;
  pthread_t thread2, thread1;

  printf("Main, initialize the read write lock\n\n\n");
  rc = pthread_rwlock_init(&rwlock, NULL); // initialise rwlock


  for (int i = 0; i < 1; i++)
  {
    printf("Main creating thread1\n\n");
    rc = pthread_create(&thread1, NULL, rdlockThread, NULL); // creating thread1
 
  }

  printf("Main creating thread2 \n\n\n"); // creating thread2
  pthread_create(&thread2, NULL, wrlockThread, NULL);


  sleep(5);

  printf("Main waiting for the threads\n\n");
  rc = pthread_join(thread1, NULL);
  

  rc = pthread_join(thread2, NULL);


  rc = pthread_rwlock_destroy(&rwlock);


  printf("Main completed\n\n");
  return 0;
}
