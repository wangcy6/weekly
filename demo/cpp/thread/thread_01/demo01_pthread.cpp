#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include<iostream>
#include <signal.h>
#include <string.h>
using namespace std;
 
void *pthread1_run(void *arg)
{
	int count=100;
	while(count--)
	{  
		//多个线程设置断点，断点是那个
		printf("i am new pthread1 %lu\n",pthread_self());
		 sleep(1);
	}
	pthread_exit(NULL);
	return 0;
}
int count2=100;
void *pthread2_run(void *arg)
{

	while(count2--)
	{   
      
		printf("i am new pthread2 %lu\n",pthread_self());
	}
	pthread_exit(NULL);
	return 0;
}

void testWatch()
{
	int watch =0;
	
	for(int i=0; i<5; i++)  
        watch+=i; 
	
	
	int a;
	int b;
	int c;
	a = 1;
	b = 2;
	c = 3;
	memset(&a,0,4*sizeof(int));
	//b 和 c的数字都没被修改了
	printf("%d %d \n", b, c);

}
void prog_exit(int signo)
{
    std::cout << "program recv signal [" << signo << "] to exit." << std::endl;
}

int main()
{  
 
	//设置信号处理
    signal(SIGINT, prog_exit);
    signal(SIGTERM, prog_exit);
	
	
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_create(&tid3,NULL,pthread1_run,NULL);
	pthread_create(&tid1,NULL,pthread1_run,NULL);
	pthread_create(&tid2,NULL,pthread2_run,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}