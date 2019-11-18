#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
using namespace std;
pthread_t tid[2];

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();
	pid_t     pid=getpid();
	/**
	Thread groups were a feature added in Linux 2.4 to support the POSIX threads notion of a set of threads that share a single PID. 
	Internally, this shared PID is the so-called thread group identifier (TGID) for the thread group. 
	Since Linux 2.4, calls to getpid(2) return the TGID of the caller.
	
	The threads within a group can be distinguished by their (system-wide) unique thread IDs (TID). A new thread's TID is available as the function result returned to the caller of clone(), and a thread can obtain its own TID using gettid(2).
	When a call is made to clone() without specifying CLONE_THREAD, then the resulting thread is placed in a new thread group whose TGID is the same as the thread's TID. This thread is the leader of the new thread group.
	https://linux.die.net/man/2/clone
	**/

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
		cout<< "process:"= pid << "pthread:" <<pid <<endl;
    }
    else
    {
        printf("\n Second thread processing\n");
		cout<< "process:"= pid << "pthread:" <<pid <<endl;
    }

    for(i=0; i<(0xFFFFFFFF);i++);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}