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
#define OFLAG O_CREAT|O_RDWR
#define MODE 00777



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
2.1 demo 2个进程交替执行


****/
struct shm_ds { // 共享存储的数据结构
	sem_t sem1;
	sem_t sem2;
};
//g++ sem_shm.cpp -lrt
int main() {
	char shm_name[] = "myshm";
	// 创建一个共享存储对象，实际是一个文件，在/dev/shm下可以找到
	int shm_fd = shm_open(shm_name, OFLAG, MODE);
	//  sem_t *sem_open(const char *name, int oflag,
    //                   mode_t mode, unsigned int value);
	//shm_open() creates and opens a new, or opens an existing, POSIX
    //  shared memory object.  A POSIX shared memory object is in effect a
    //  handle which can be used by unrelated processes to mmap(2) the same
    //  region of shared memory
	if (shm_fd < 0) {
		perror("shm_open error");
		return 0;
	}
	// 切分文件到一个需要的大小，这里选取st_size=sizeof(shm_ds);
	ftruncate(shm_fd, sizeof(shm_ds));
	// 将刚才的共享文件映射到内存
	shm_ds *p= (shm_ds *)mmap(NULL, sizeof(shm_ds), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (p == NULL) {
		perror("mmap error");
		return 0;
	}
	// 初始化信号量，注意第二个参数为1，多个进程间可共享该信号量
	// 可以尝试将 第二个参数设置为0，观察一下会发生什么
	sem_init(&(p->sem1), 1, 0);
	sem_init(&(p->sem2), 1, 0);

	pid_t child_pid = fork();
	if (child_pid < 0) {
		perror("fork error");
		return 0;
	}
	else if (child_pid == 0) {
		for (int i = 0; i < 5; i++) {
			sem_wait(&(p->sem2)); //等待，激活，然后等待
			printf("(%d). child  pid=%d\n",i, getpid());
			sem_post(&(p->sem1));//通知。
		}
	}
	else {
		 //parent
		for (int i = 0; i < 5; i++) {
			sem_post(&(p->sem2)); //通知+1
			sem_wait(&(p->sem1)); //然后等待中，
			//为什么激活后，不需要锁，无竞争资源。
			printf("(%d). father  pid=%d\n",i, getpid());
			sleep(1);
		}
		// 父进程等待子进程结束，这样防止将死进程且保证父进程最后结束
		int stat;
		wait(&stat);
		// 一定不要删除掉那个共享文件（除非你有意保留）
		// 如果不删除，程序结束后在 /dev/shm 下可以找到 "myshm" 这个文件；
		// 下次还要创建 "myshm" 将失败
		shm_unlink(shm_name);
	}
}
/****
 不同进程交替输出
 (0). child  pid=29736
(0). father  pid=29735
(1). child  pid=29736
(1). father  pid=29735
(2). child  pid=29736
(2). father  pid=29735
(3). child  pid=29736
(3). father  pid=29735
(4). child  pid=29736
(4). father  pid=29735

****/
//http://www.gonglin91.com/semaphores/