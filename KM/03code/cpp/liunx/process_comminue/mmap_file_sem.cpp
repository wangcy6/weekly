#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;
#include "unpipc.h"
struct shared {
  sem_t	mutex;		/* the mutex: a Posix memory-based semaphore */
  int	count;		/* and the counter */
} shared;

//g++  --std=c++11 mmap_file_sem.cpp -lrt
int main(int argc, char **argv)
{
	int		fd, i, nloop;
	struct shared 	*ptr;

	if (argc != 3)
		err_quit("usage: incr3 <pathname> <#loops>");
	nloop = atoi(argv[2]);

	/* 4open file, initialize to 0, map into memory */
	fd = open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
	write(fd, &shared, sizeof(struct shared)); //不需要结构转换吗，是的 。
	// boost::serialization C++ 将对象写入文件之后再读取它？
	
	
	ptr = (shared*)mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE,
			   MAP_SHARED, fd, 0);
	close(fd);
	//不需要结构转换吗

	/* 4initialize semaphore that is shared between processes */
	sem_init(&ptr->mutex, 1, 1);

	setbuf(stdout, NULL);	/* stdout is unbuffered */
	//上面的操作都是相同的。
	if (fork() == 0) {		/* child */
		for (i = 0; i < nloop; i++) 
		{
			sem_wait(&ptr->mutex);
			printf("child: %d\n", ptr->count++);
			sem_post(&ptr->mutex);
		}
		exit(0);
	}

		/* 4parent */
	for (i = 0; i < nloop; i++) 
	{
		sem_wait(&ptr->mutex);
		printf("parent: %d\n", ptr->count++);
		sem_post(&ptr->mutex);
	}
	exit(0);
}

/**
parent: 0
parent: 1
parent: 2
child: 3
child: 4
child: 5
**/
/**
1 mmap是什么
优势
1 读写文件避免了 read() 和 write() 系统调用，也避免了数据的拷贝。
2 除了潜在的页错误，读写 map 后的文件不引起系统调用或者上下文切换。就像访问内存一样简单。
3 多个进程 map 同一个对象，可以共享数据。
4 可以直接使用指针来跳转到文件某个位置，不必使用 lseek() 系统调用。

https://github.com/double-free/tiny-projects/tree/master/mmap
https://nieyong.github.io/wiki_cpu/mmap%E8%AF%A6%E8%A7%A3.html
2 mmap是什么解决了什么问题

通常使用mmap()的三种情况： 共享内存进程通信 

共享内存的优缺点
使用共享内存的优缺点如下所述 。

优点：使用共享内存进行进程间的通信非常方便，而且函数的接口也简单，数据的
共享还使进程间的数据不用传送，而是直接访问内存，也加快了程序的效率。 同时，它也不
像无名管道那样要求通信的进程有一定的父子关系 。

缺点：共享 内存没有提供同步的机制，这使得在使用共享 内存进行进程间通信时，
往往要借助其他的手段来进行进程间的同步工作 。
***/
