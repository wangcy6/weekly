//本文介绍如何将一个 Web 应用，启动为守护进程。??
//http://www.ruanyifeng.com/blog/2016/02/linux-daemon.html
//怎么才能让它变成系统的守护进程（daemon），成为一种服务（service），一直在那里运行呢???
//后台任务"与"前台任务"的本质区别只有一个：是否继承标准输入。
//所以，执行后台任务的同时，用户还可以输入其他命令。
//变为"后台任务"后，一个进程是否就成为了守护进程呢？或者说，用户退出 session 以后，"后台任务"是否还会继续执行？
//https://stackoverflow.com/questions/4298741/how-bash-handles-the-jobs-when-logout
//Off: Background jobs will NOT be terminated with SIGHUP when shell exits.
//session 就肯定不会向它发出SIGHUP信号
// nohup node server.js &
// nohup命令对server.js进程做了三件事。
// 阻止SIGHUP信号发到这个进程。
// 关闭标准输入。该进程不再能够接收任何输入，即使运行在前台。
// 重定向标准输出和标准错误到文件nohup.out。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 守护进程初始化函数
/**
编写守护进程的一般步骤步骤：

（1）在父进程中执行fork并exit推出；

（2）在子进程中调用setsid函数创建新的会话；

（3）在子进程中调用chdir函数，让根目录 ”/” 成为子进程的工作目录；

（4）在子进程中调用umask函数，设置进程的umask为0；

（5）在子进程中关闭任何不需要的文件描述符

**/
void init_daemon()
{
    pid_t pid;
    int i = 0;

    if ((pid = fork()) == -1) {
        printf("Fork error !\n");
        exit(1);
    }
    if (pid != 0) {
        exit(0);        // 父进程退出
    }

    setsid();           // 子进程开启新会话，并成为会话首进程和组长进程
    if ((pid = fork()) == -1) {
        printf("Fork error !\n");
        exit(-1);
    }
    if (pid != 0) {
        exit(0);        // 结束第一子进程，第二子进程不再是会话首进程
    }
    chdir("/tmp");      // 改变工作目录
    umask(0);           // 重设文件掩码
    for (; i < getdtablesize(); ++i) {
       close(i);        // 关闭打开的文件描述符
    }

    return;
}

int main(int argc, char *argv[])
{
    int fp;
    time_t t;
    char buf[] = {"This is a daemon:  "};
    char *datetime;
    int len = 0;
    //printf("The NOFILE is: %d\n", NOFILE);
    //printf("The tablesize is: %d\n", getdtablesize());
    printf("The pid is: %d\n", getpid());

    // 初始化 Daemon 进程
    init_daemon();

    // 每隔一分钟记录运行状态
    while (1) {
        if (-1 == (fp = open("./daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600))) {
          printf("Open file error !\n");
          exit(1);
        }
        len = strlen(buf);
        write(fp, buf, len);
        t = time(0);
        datetime = asctime(localtime(&t));
        len = strlen(datetime);
        write(fp, datetime, len);
        close(fp);
        sleep(60);
    }

    return 0;
}