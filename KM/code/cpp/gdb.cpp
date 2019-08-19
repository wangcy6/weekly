/** 
 * @FileName    gdb_pthread.c
 * @Describe    A simple example for the debug of multiprocess and multithreading using gdb in linux system.
 * @Author      vfhky 2016-02-25 22:48 https://typecodes.com/cseries/multilprocessthreadgdb.html
 * @Compile     gcc gdb_pthread.c -g  -lpthread   -o gdb_pthread
                
 * @Reference   http://blog.csdn.net/pbymw8iwm/article/details/7876797
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


//Parent process handle.
void Parent();
//Child process handle.
void Child();
//Parent process handle after generate a thread.
void * ParentDo( char *argv );

int main( int argc, const char **argv )
{
    int pid;
    pid = fork();
    if(pid != 0)        //add the first breakpoint.
        Parent();
    else
        Child();
    return 0;
}

//Parent process handle.
void Parent()
{
    pid_t pid = getpid();
    char cParent[] = "Parent";
    char cThread[] = "Thread";
    pthread_t pt;

    printf( "[%s]: [%d] [%s]\n", cParent, pid, "step1" );

    if( pthread_create( &pt, NULL, (void *)*ParentDo, cThread ) )
    {
        printf( "[%s]: Can not create a thread.\n", cParent );
    }

    ParentDo( cParent );
    sleep(1);
}

void * ParentDo( char *argv )
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();     //Get the thread-id selfly.
    char tprefix[] = "thread";

    printf( "[%s]: [%d] [%s] [%lu] [%s]\n", argv, pid, tprefix, tid, "step2" );         //add the second breakpoint.
    printf( "[%s]: [%d] [%s] [%lu] [%s]\n", argv, pid, tprefix, tid, "step3" );

    return NULL;
}

void Child()
{
    pid_t pid = getpid();
    char prefix[] = "Child";
    printf( "[%s]: [%d] [%s]\n", prefix, pid, "step1" );
    return;
}