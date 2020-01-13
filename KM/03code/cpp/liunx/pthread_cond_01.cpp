#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
//该函数增加count数值
void * creator(void * arg)
{
    cout << "creator add lock" << endl;
    pthread_mutex_lock(&mutex);

    count ++;

    cout << "in creator count is : " << count << endl;
    //条件满足时发送信号
    if(count > 0)
    {

        pthread_cond_signal(&cond);
        //pthread_cond_signal函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程,使其脱离阻塞状态,继续执行
    }

    
    cout << "creator release lock" << endl;
    
    pthread_mutex_unlock(&mutex);
  //https://linux.die.net/man/3/pthread_cond_wait
// pthread_cond_wait 会原子地执行2个动作

// 给互斥锁mptr解锁
// 把调用线程投入睡眠

    return NULL;

}

//该函数减少count数值
void * consumer(void * arg)
{
    cout << "consumer add lock" << endl;

    pthread_mutex_lock(&mutex);
    //当条件不满足时等待
    if(count <= 0)
    {
        cout << "begin wait" << endl;
        pthread_cond_wait(&cond,&mutex);
        cout << "end wait" << endl;
        //解锁->阻塞->信号（唤醒）->上锁
    }

    count --;

    cout << "in consumer count is " << count << endl;

    pthread_mutex_unlock(&mutex);

    cout << "consumer release lock" << endl;
    
    return NULL;
    
}


int main()
{
    //两个线程，一个生产者线程一个消费者线程
    pthread_t createthread,consumethread;

     pthread_create(&consumethread, NULL, consumer, NULL);
　　 sleep(2);
    pthread_create(&createthread, NULL, creator, NULL);
    
    //主进程等待两个线程结束
    pthread_join(createthread, NULL);
    pthread_join(consumethread, NULL);
    return 0;
}