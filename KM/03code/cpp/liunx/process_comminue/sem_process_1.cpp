#include <unistd.h>
#include <cstdio>
#include <cstdio>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h> //O_CREATE O_EXCL
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
/****
一. 什么是信号量
信号量：
1. 保证进程同步执行

有名信号量由sem_open打开，
其第一个参数是一个字符串，正是该信号量的名字；
有名信号量由内核持续，正是因此多个进程间才能利用它；
由于是内核持续，一个进程结束了，信号量并不会被关闭删除，因而最后一个退出的进程，
要负责关闭有名信号量并且将其从内核中删除

2.保证进程内线程同步执行：
无名信号量由sem_init打开，不需要名字，进程持续，进程结束了，信号量就没了，
因此无名信号量往往在进程内使用，因此多用于线程间；

锁：解决互斥问题，无法保证同步
二. 信号量解决了什么问题
2.1 demo 2个进程交替执行。


****/

int main() 
{
	char file_name[] = "share_file";
	char mutex_name1[] = "psmutex1";
	char mutex_name2[] = "psmutex2";
     //ipcs
	//用sem_open创建有名信号量，由内核持续，O_CREAT表示创建
	sem_t *mutex1 = sem_open(mutex_name1, O_CREAT, 0644, 0); //已经存在
	sem_t *mutex2 = sem_open(mutex_name2, O_CREAT, 0644, 0);//已经存在

	for (int i = 0; i < 5; i++) 
	{
		sem_post(mutex2);//post之后，激活其他线程，
		sem_wait(mutex1);//其他进程执行后，在发送post
		FILE *fp = fopen(file_name, "a+");
		fprintf(fp, "(%d).semshare1  pid = %d\n", i,getpid());
		fclose(fp);
	}
	sleep(3);
	//关闭信号量，只是在进程层面关系，内核仍然持有该信号量
	sem_close(mutex1);
	sem_close(mutex2);
	//unlink才是从内核中将该信号量删除
	sem_unlink(mutex_name1);
	sem_unlink(mutex_name2);
	return 0;
}