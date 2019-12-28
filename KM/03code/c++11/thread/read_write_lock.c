#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//结构体设置方便对比读写锁与互斥锁
struct Ticket{
    int remain;//余票数
    pthread_rwlock_t rwlock;//读写锁
    pthread_mutex_t mlock;//互斥锁
}ticket;
//https://www.youtube.com/watch?v=_vfZhdTgA5A
//https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-7%3A-The-Reader-Writer-Problem

int lock = 0;

//查询票的线程
void* query(void* arg) {
    int name = (int)arg;
    sleep(rand() % 5 + 1);
    ///参数 1：表示使用读写锁
    if (lock == 1){
        pthread_rwlock_rdlock(&ticket.rwlock);//读模式加锁 5
        // pthread_rwlock_rdlock(&ticket.rwlock);
        // pthread_rwlock_rdlock(&ticket.rwlock);
        // pthread_rwlock_rdlock(&ticket.rwlock);
        // pthread_rwlock_rdlock(&ticket.rwlock);
        printf("%03d rdlock \n", name);
    }else if (lock == 2){
        pthread_mutex_lock(&ticket.mlock);
    }
    int remain = ticket.remain;
    sleep(1);
    printf("%03d query: %d\n", name, remain);
    
    if(lock == 1){
        pthread_rwlock_unlock(&ticket.rwlock);//5
        // pthread_rwlock_unlock(&ticket.rwlock);
        // pthread_rwlock_unlock(&ticket.rwlock);
        // pthread_rwlock_unlock(&ticket.rwlock);
        // pthread_rwlock_unlock(&ticket.rwlock);
        //pthread_rwlock_unlock(&ticket.rwlock);

    }else if(lock == 2){
        pthread_mutex_unlock(&ticket.mlock);
    }
    return NULL;
}
//抢票的线程
void* buy(void* arg) {
    int name = (int)arg;
    if(lock == 1){
        pthread_rwlock_wrlock(&ticket.rwlock);//写模式加锁 5
        {
            pthread_rwlock_wrlock(&ticket.rwlock);//必须成对出现，不能连续加锁
            pthread_rwlock_unlock(&ticket.rwlock);
        }
        {
            pthread_rwlock_wrlock(&ticket.rwlock);//必须成对出现，不能连续加锁
            pthread_rwlock_unlock(&ticket.rwlock);
        }

        printf("%03d wrlock lock  \n", name);
        //The calling thread
       //may deadlock if at the time the call is made it holds the read-write  lock
    }else if(lock == 2){
        pthread_mutex_lock(&ticket.mlock);
        
        {
            pthread_mutex_lock(&ticket.mlock); //互斥锁 被自己反复加锁2次,形成死锁
            pthread_mutex_unlock(&ticket.mlock);
        }
    }
    int remain = ticket.remain;
    remain -= 30;
    sleep(1);
    ticket.remain = remain;
    printf("%03d buy 10 tickets\n", name);
    
    if(lock == 1){
        pthread_rwlock_unlock(&ticket.rwlock); // 成对出现  5
        //pthread_rwlock_unlock(&ticket.rwlock); // 连续解锁是有问题的
    }else if(lock == 2){
        pthread_mutex_unlock(&ticket.mlock);
    }
    sleep(rand() % 5 + 2);
    
    return NULL;
}
//gcc  -pthread -w read_write_lock.c -g
int main(int argc, char* argv[]) {
    lock = 0;
    if(argc >= 2){
        lock = atoi(argv[1]);
       
    }
    int len =100;
    int names[len];//100个线程名字
    pthread_t tid[len];//100个线程存储数组
    memset(&tid,0,sizeof(tid));
    int i;
    
    for (i = 0; i < len; ++i){
        names[i] = i;
    }
    ticket.remain = 1000;//余票初始为1000张
    
    printf("余票数量 = %d\n", ticket.remain);
    
    pthread_rwlock_init(&ticket.rwlock, NULL);
    pthread_mutex_init(&ticket.mlock, NULL);
    
    for (i = 0; i < len; i++) {
        
    
        pthread_create(&tid[i], NULL, buy, (void*)names[i]);
    
        pthread_create(&tid[i], NULL, query, (void*)names[i]);
        
    }
    
    for (i = 0; i < len; i++) {
        if (tid[i] > 0)
        {
           pthread_join(tid[i], NULL);
        }
       
    }
    
    pthread_rwlock_destroy(&ticket.rwlock);
    pthread_mutex_destroy(&ticket.mlock);
    printf("余票数量 = %d\n", ticket.remain);
    
    return 0;
}

/***
 * 读写锁示例
程序 trainticket 中，有 100 个线程，其中 90 个线程是查余票数量的，
只有 10 个线程抢票，每个线程一次买 10 张票。
初始状态下一共有 1000 张票。因此执行完毕后，还会剩下 900 张票。
程序 trainticket 在运行的时候需要传入参数，
即 ./trainticket <0|1|2>:
参数 0：表示不加任何锁
参数 1：表示使用读写锁
参数 2：表示使用互斥量
https://stackoverflow.com/questions/55727735/description-of-the-members-of-struct-pthread-rwlock-t
 */