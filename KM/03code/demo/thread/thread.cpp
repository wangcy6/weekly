#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using  namespace std;

void* func(void* arg)
{
    pthread_t main_tid = *static_cast<pthread_t*>(arg);
	//Threads are identified using PIDs and TGID (Thread group id)
	pid_t pid =getpid();
	pthread_t tid =pthread_self();
	std::cout << "Child Thread " << tid << "in Process " << getpid<< std::endl;
    pthread_cancel(main_tid);
	
	/*	  
	  tast_struct里面维护了两套signal_pending，一套是线程组共用的，一套是线程独有的。	通过kill发送的致命信号被放在线程组共享的signal_pending中，可以任意由一个线程来处理。
	  而通过pthread_kill发送的信号被放在线程独有的signal_pending中，只能由本线程来处理。
	*/
    while (true)
    {    //主线程退出后，子线程依然运行
        printf("child loops\n");
    }
    return NULL;
}
//主线程随进程一起退出
void* func2(void* arg)
{   
    pid_t pid =getpid();
	pthread_t tid =pthread_self();
	std::cout << "Child Thread " << tid << "in Process " << getpid<< std::endl;
    while (true)
    {
		std::cout << "child loops Child Thread " << tid << "in Process " <<getpid<< std::endl;
    }
    return NULL;
}
//g++  -pthread thread.cpp 
int main(int argc, char* argv[])
{
    pthread_t main_tid = pthread_self();
    pthread_t tid = 0;
	pid_t pid =getpid();
	std::cout << "Main Thread " << tid << "in Process " <<getpid<< std::endl;
	
	
    //pthread_create(&tid, NULL, func, &main_tid);
	 pthread_create(&tid, NULL, func2, &main_tid);
    while (0)
    {
        printf("main loops\n");
    }
    sleep(1);
    printf("main exit\n");
    return 0;
}