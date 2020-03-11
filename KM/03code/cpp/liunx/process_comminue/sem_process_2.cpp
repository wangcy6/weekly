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
信号量：跨进程使用
****/
int main() {
	char file_name[] = "share_file";
	char mutex_name1[] = "psmutex1";
	char mutex_name2[] = "psmutex2";
	// 打开已有的信号量
	sem_t *mutex1 = sem_open(mutex_name1, O_EXCL);
	sem_t *mutex2 = sem_open(mutex_name2, O_EXCL);

	for (int i = 0; i < 5; i++) {
		sem_wait(mutex2); //程序启动 马上阻塞在这里，等待被激活。
		FILE *fp = fopen(file_name, "a+");
		fprintf(fp, "(%d).semshare2  pid = %d\n", i,getpid());
		fclose(fp);
		sem_post(mutex1);
	}
	return 0;
}