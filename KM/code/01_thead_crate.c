#include<stdio.h>  
#include<pthread.h>  
#include<string.h>  
#include<sys/types.h>  
#include<unistd.h>  
pthread_t ntid;  
  
void printids(const char *s)  
{  
    pid_t pid;  
    pthread_t tid;  
  
    pid = getpid();  
    tid = pthread_self();  
    printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int)pid,(unsigned int)tid,(unsigned int)tid);  
  
}  
  
void *thread(void *arg)  
{  
    printids("new thread:");  
    return ((void *)0);  
}  

//gcc -o pthread 01_thead_crate.c  -lpthread
int main()  
{  
    int temp  
    if((temp=pthread_create(&ntid,NULL,thread,NULL)))  
    {  
        printf("can't create thread: %s\n",strerror(temp));  
        return 1;  
     }  
     printids("main thread:");  
     sleep(1);
//   pthread_join(ntid,NULL);  
     return 0;  
}  