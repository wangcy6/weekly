---
title: "Linux内核设计与实现"
date: 2019-10-10T17:02:43+08:00
description: ""
draft: false
tags: ["FQA"]
categories: ["Book"]
---



## 中断与锁（第7 ，8，9，10 章节）



### 1. 延迟处理机制

![延迟处理](https://i.loli.net/2019/11/28/4TuvtYr26XEcMCD.png)



#### 中断特点

- 中断处理程序不是可[重入](https://zh.wikipedia.org/wiki/%E5%8F%AF%E9%87%8D%E5%85%A5)的。因为屏蔽了中断，根本不会发生切换。同类[自旋锁是不可重入](https://my.oschina.net/anur/blog/1573625)的
- 中断处理进程，只能采用自旋锁（短期互斥原语），不能长期互斥原语（这会导致进程睡眠）【epoll原理 不能长期阻塞】
- 随时都可能发生，异步的。



中断处理程序 ---ksoftirqd

~~~shell
ps -ef |grep ksoftirqd
root         3     2  0  2018 ?        00:00:06 [ksoftirqd/0]
root        29     2  0  2018 ?        00:00:01 [ksoftirqd/1]
root        34     2  0  2018 ?        00:00:00 [ksoftirqd/2]
root        39     2  0  2018 ?        00:00:00 [ksoftirqd/3]
root        44     2  0  2018 ?        00:00:00 [ksoftirqd/4]
root        49     2  0  2018 ?        00:00:00 [ksoftirqd/5]
root        54     2  0  2018 ?        00:00:00 [ksoftirqd/6]
root        59     2  0  2018 ?        00:00:00 [ksoftirqd/7]
~~~



#### 流程

![image.png](https://i.loli.net/2019/11/28/fHT9uVRo73cvl5Z.png)

![image.png](https://i.loli.net/2019/11/28/Wod1ue8ylLxizaG.png)



#### 结构

~~~c
/* 用于描述一个软中断 */
struct softirq_action
{
    /* 软中断的处理函数 */        
    void    (*action)(struct softirq_action *);
};

/* 6个软中断描述符都保存在此数组 */
static struct softirq_action softirq_vec[NR_SOFTIRQS] __cacheline_aligned_in_smp;


struct tasklet_struct
{
    struct tasklet_struct *next;      /* 指向链表下一个tasklet */
    unsigned long state;              /* tasklet状态 TASKLET_STATE_SCHED表示处于链表中，TASKLET*/
                                      /* _STATE_RUN表示正在运行*/
    atomic_t count;                   /* 禁止计数器，调用tasklet_disable()会增加此数，tasklet*/
                                      /* enable()减少此数 */
    void (*func)(unsigned long);      /* 处理函数 */
    unsigned long data;               /* 处理函数使用的数据 */
};
struct tasklet_head {
    struct tasklet_struct *head;
    struct tasklet_struct **tail;
};
~~~



### 2. 锁



##### 读写锁 (ReentrantReadWriteLock)

特点

- 可重入互斥锁（ reentrant mutex ）

> 同一[线程](https://zh.wikipedia.org/wiki/线程)对其多次加锁不会产生[死锁](https://zh.wikipedia.org/wiki/死锁)。可重入互斥锁也称**递归互斥锁**  



#### 自旋锁

特点

-  不可重入锁

  > 若有同一线程两调用lock() ，会导致第二次调用lock位置进行自旋，产生了死锁 

  



------------------------------------------------华丽分隔符------------------------------------------------------------------------

**可重入性**

>  若一个[程序](https://zh.wikipedia.org/wiki/程序)或[子程序](https://zh.wikipedia.org/wiki/子程序)可以“在任意时刻被[中断](https://zh.wikipedia.org/wiki/中断)然后操作系统调度执行另外一段代码，这段代码又调用了该子程序不会出错”，则称其为**可重入**（reentrant或re-entrant）的。
>
> 即当该子程序正在[运行时](https://zh.wikipedia.org/wiki/執行期)，执行线程可以再次进入并执行它，仍然获得符合设计时预期的结果。 
>
> 若一个[函数](https://zh.wikipedia.org/wiki/函数)是可重入的，则该函数应当满足下述条件：
>
> - 不能含有静态（全局）非常量数据。
> - 不能返回静态（全局）非常量数据的地址。
> - 只能处理由调用者提供的数据。
> - 不能依赖于[单实例模式](https://zh.wikipedia.org/wiki/单实例模式)资源的锁。
> - 调用(call)的函数也必需是可重入的。
>
> 啥意思 就是 
>
> 你在执行一个函数的时候，切换出去别人在执行同样的函数，或者其他函数。而不出问题

------------------------------------------------华丽分隔符------------------------------------------------------------------------

### 改造后的自旋锁

[例子](https://kanonjz.github.io/2017/12/27/reentrantlock-and-spinlock/)

~~~java
public class SpinLock {
    private AtomicReference<Thread> owner =new AtomicReference<>();
    private int count =0;
    public void lock(){
        Thread current = Thread.currentThread();
        if(current==owner.get()) {
            count++;
            return ;
        }
        //compareAndSet(Thread expect, Thread update)
        //自旋锁的自旋就是体现在这里
        while(!owner.compareAndSet(null, current)){

        }
    }
    public void unlock (){
        Thread current = Thread.currentThread();
        if(current==owner.get()){
            if(count!=0){
                count--;
            }else{
                owner.compareAndSet(current, null);
            }

        }

    }
}
注意两点：
1. 修改之后，就可以重复进入代码区域了
~~~



## 中断与信号

## [linux可重入、异步信号安全和线程安全](https://www.cnblogs.com/alantu2018/p/8446917.html)

**不可重入的几种情况**：

使用静态数据结构，比如getpwnam，getpwuid：如果信号发生时正在执行getpwnam，信号处理程序中执行getpwnam可能覆盖原来getpwnam获取的旧值

- 调用malloc或free：如果信号发生时正在malloc（修改堆上存储空间的链接表），信号处理程序又调用malloc，会破坏内核的数据结构 new

- 使用标准IO函数，因为好多标准IO的实现都使用全局数据结构，比如printf(文件偏移是全局的)

- 函数中调用longjmp或siglongjmp：信号发生时程序正在修改一个数据结构，处理程序返回到另外一处，导致数据被部分更新。

  

  2. 不可重入函数不能由多个线程使用。

  **如果将对临界资源的访问加锁，则这个函数是线程安全的；但如果重入函数的话加锁还未释放，则会产生死锁，因此不能重入**。

  

  

### 大家都在讨论

- Java多线程系列——深入重入锁ReentrantLock 【done_很好】

  https://www.cnblogs.com/zhengbin/p/6503412.html

- 深入理解读写锁ReentrantReadWriteLock 【reading】

  [ReentrantLock的实现语义与使用场景](https://www.cnblogs.com/dongguacai/p/5992838.html)[done_good!!!!]

  https://www.cnblogs.com/dongguacai/p/5994381.html

  https://www.jianshu.com/p/4a624281235e

- https://www.cnblogs.com/charlesblc/p/6188364.html

-  https://kanonjz.github.io/2017/12/27/reentrantlock-and-spinlock/ 

- http://www.liuhaihua.cn/archives/608699.html 

-  https://my.oschina.net/anur/blog/1573625 