include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_func(void *args)
{
    printf("tid: %u pid: %u thread id: %un", getpid(), syscall(224), pthread_self());
    while(1) {
        sleep(10);
    }
}
//8MB，8MB*382就是3056MB
//http://0xffffff.org/2013/08/02/20-linux-thread-address-space/
//Linux线程的前世今生
//线程眼中的线性地址空间
//http://0xffffff.org/2013/07/30/19-linux-thread-history/
int main(int argc, char *argv[])
{
    pthread_t thread;
    int count = 0;
    while (pthread_create(&thread, NULL, thread_func, NULL) == 0) {
        sleep(1);
        count++;
    }
    perror("Create Error:");
    printf("Max Count:%dn", count);
    return EXIT_SUCCESS;
}


//https://www.ibm.com/developerworks/cn/linux/l-threading.html
//https://akkadia.org/drepper/nptl-design.pdf

/**
变量值的共享可以使用public static变量的形式，
所有的线程都使用同一个public static变量。
但如果想实现每一个线程都有自己的共享变量，
则需要使用ThreadLocal类。 
类ThreadLocal主要解决的就是每个线程绑定自己的值，
可以将ThreadLocal类比喻呈全局存放数据的盒子，盒子中可以存储每个线程的私有数据。
通过get()和set()方法可以获取和设置每个线程的私有数据。
覆写该类的initialValue()方法可以使变量初始化，从而解决get()返回null的问题。
InheritableThreadLocal类可在子线程中取得父线程继承下来的值。
Chap4. Lock的使用**/
