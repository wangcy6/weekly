



# 第一天 进程和线程的区别

###  缘起



![201909](../images/201909.png)



修正：这面简单问题-->这么简单的问题。

###  分析

#### 结论：

进程和线程的主要区别应该是在**创建的时候** **线程** **需要共享了（父子）进程的资源  ，初次之外 应该是一样的**。

在liunx系统中 没有进程和线程的区别 统称 “task” 进程标志（task_struct） 进行统一描述



#### 继续分析：



严格意义上讲, 并没有进程,线程的区别

Linus Torvalds 增加在邮件说写到

> Both threads and processes are really just one thing: a "context of
> execution". Trying to artificially distinguish different cases is just
> self-limiting. 
>
> A "context of execution", hereby called COE, is just the conglomerate of 
> all the state of that COE. That state includes things like CPU state 
> (registers etc), MMU state (page mappings), permission state (uid, gid) 
> and various "communication states" (open files, signal handlers etc).

COE :执行上下文

一个进程所包含的资源(或者称之为状态)有, 

- CPU状态(比如寄存器), 

- 内存状态(Memory management unit, 内存映射),

-  权限状态(用户是谁, 在哪个组里), 

- 以及一些其他的可通信的状态, 比如打开的文件, 接受的信号等.


1. 进程：
   - CPU state: registers etc   （1）
   - MMU state: page mappings，记录当前进程的虚拟内存地址到物理内存地址的映射的信息。 （2）
   - permission state: uid, gid （3）
   - various “communication states”: open files, signal handlers etc （4）
2. 线程：
   - CPU state: registers
   - - possibly some other minial state
   - all others: shared from process（共享的范围 什么？  2  3  4 ）

![1547177329624](../images/1547177329624.png)



可以看到，进程和线程都是'COE', ( *stay at a high level discussion.*) 

线程和进程的有各自的 CPU state （栈抽象成cpu） ------不相同 

![不相同](../images/1547193443747.png)

线程：

MMU state，permission stat， various “communication states是共享进程的。---相同



**截止到目前 你看到进程和线程还是有区别的，线程共享资源，进程不共享资源 这不是区别吗？**



a light-weight process (LWP) 

Linux下内核其实本质上没有线程的概念, Linux下线程其实上是与其他进程共享某些资源的进程而已。但是我们习惯上还是称他们为线程或者轻量级进程 线程是进程的子集 



>The way Linux thinks about this (and the way I want things to work) is that
>there _is_ no such thing as a "process" or a "thread". There is only the
>totality of the COE (called "task" by Linux). 
>
>Different COE's can share parts
>of their context with each other, and one _subset_ of that sharing is the
>traditional "thread"/"process" setup, but that should really be seen as ONLY
>a subset (it's an important subset, but that importance comes not from
>design, but from standards: we obviusly want to run standards-conforming
>threads programs on top of Linux too). 
>
>Linux思考这个问题的方式(以及我希望工作的方式)是这样的
>
>没有所谓的“进程”或“线程”。只有
>
>COE的总体(Linux称为“任务”)。不同的COE可以共享部件
>
>它们之间的上下文，而共享的一个_subset_是
>
>传统的“线程”/“进程”设置，但实际上应该只将其视为
>
>一个子集(它是一个重要的子集，但是这个重要性不是来自它
>
>设计，但从标准:我们显然希望运行符合标准的
>
>线程程序也在Linux之上)。

#### 继续分析   clone函数

#### 进程和线程的创建

![6791b920-b269-42ab-a7bf-5f7bde388f5b](../images/6791b920-b269-42ab-a7bf-5f7bde388f5b.png)

进程的创建的 而fork（）本身是由clone（）实现的

> clone(SIGCHLD,0);



线程创建：pthread_create-->clone

> clone(CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND,0);

用strace 跟踪pthread_create创建过程：

> clone(child_stack=0x7fd4174b8ff0, flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, parent_tidptr=0x7fd4174b99d0, tls=0x7fd4174b9700, child_tidptr=0x7fd4174b99d0) = 16477



clone参数的对应作用如下： 
CLONE_VM：父子进程共享地址空间 

CLONE_FS：父子进程共享文件系统信息 
CLONE_FILES：父子进程共享打开的文件 
CLONE_SIGHAND：父子进程共享信号处理函数及被阻断的信号



- 进程：可以共享，也可以不共享（have or  not have ）

- 线程共享了父子进程之间的各种资源 a light-weight process (LWP) （must）





#### 塔山：

-  http://man7.org/linux/man-pages/man2/clone.2.html
- http://lkml.iu.edu/hypermail/linux/kernel/9608/0191.html
- Linux进程线程源码浅析
- Linux 中的各种栈：进程栈 线程栈 内核栈 中断栈







#### 作业：协程呢 （从COE 程序运行空间角度分析）? 

![img](https://www.itcodemonkey.com/data/upload/portal/20180620/1529501499784110.jpg)









 协程，又称微线程，纤程。英文名Coroutine

> A coroutine is a **function** that can **suspend** its execution (yield) until the given given **Yield Instruction** finishes.



![img](https://mmbiz.qpic.cn/mmbiz_png/NtO5sialJZGoRJcJhcDvDdtT2AQRI72pEXgJj2tLqX5A0oQ7QGyOWZOKyK3gibLWEjbxNbHEwo1CP8uo7kCMTyYA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

协程：

- CPU state: registers etc   （各自的寄存器 ！！！！）
- MMU state: page mappings，（共享线程）
- permission state: uid, gid （不需要，属于应用层，系统不知道）
- various “communication states”: open files, signal handlers etc （共享线程）

【待处理 有点难】

Protothreads：[一个“蝇量级” C 语言协程库](http://coolshell.cn/articles/10975.html)
libco:[来自腾讯的开源协程库libco介绍](http://www.cnblogs.com/bangerlee/p/4003160.html)，[官网](http://code.tencent.com/libco.html)
coroutine:[云风的一个C语言同步协程库](https://github.com/cloudwu/coroutine/),[详细信息](http://blog.codingnow.com/2012/07/c_coroutine.html)

目前看到大概有四种实现协程的方式：

· 第一种：利用glibc 的 ucontext组件(云风的库)

· 第二种：使用汇编代码来切换上下文([实现c协程](http://www.cnblogs.com/sniperHW/archive/2012/06/19/2554574.html))

· 第三种：利用C语言语法switch-case的奇淫技巧来实现（Protothreads)

· 第四种：利用了 C 语言的 setjmp 和 longjmp（ [一种协程的 C/C++ 实现](http://www.cnblogs.com/Pony279/p/3903048.html),要求函数里面使用 static local 的变量来保存协程内部的数据）



塔山

- C++协程(1):协程原理及实现方式概述
- 浅谈我对协程的理解
- 源漫画：什么是协程？[程序员小灰](https://mp.weixin.qq.com/s/57IERpGIlvRwYCh6vSbMDA) 写的



#### 扩展阅读： 整天说堆栈，堆栈是啥意思







- 堆栈都是虚拟地址

![eab8cae7-3e1b-4c2b-b1ac-e490f3af11e6](../images/eab8cae7-3e1b-4c2b-b1ac-e490f3af11e6.png)

- 虚拟地址都会缺页

![1ad966ed-2607-4aa3-88f1-e5f4af0ff57b](../images/1ad966ed-2607-4aa3-88f1-e5f4af0ff57b.png)

- 多核下多进程多线程

![421d5eb6-0f29-451b-9c74-95840145eda5](../images/421d5eb6-0f29-451b-9c74-95840145eda5.png)

塔山

- 9.7 深入理解计算机系统：Case Study: The Intel Core i7/Linux Memory System （正在学习中）
- Understanding the Java Memory Model （正在学习中）





# 第二天 map和unordered_map

## 1. 优缺点

#### unordered_map:

unordered_map是基于hash_table实现

- ##### 优点：

  ​	Hash表，在数据无冲突 的情况下，插入、查询和删除都可以认为是O(1)的时间复杂度，最完美

  ​       常数时间，操作

  https://en.wikipedia.org/wiki/Hash_table

  | Algorithm  | **Average** | **Worst case** |
  | ---------- | ----------- | -------------- |
  | **Space**  | O(*n*）     | O(*n*）        |
  | **Search** | O(1)        | O(*n*）        |
  | **Insert** | O(1)        | O(*n*）        |
  | **Delete** | O(1)        | O(*n*)         |

  ![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg/1280px-Hash_table_3_1_1_0_1_0_0_SP.svg.png)

  ### 缺点： .

  链地址法冲突的缺点

  

  ##### 问题1  哈希表大小设置不合理的，导致频繁扩容，/扩容期间造成内存不足等情况

  

  <u>意思是说：vector扩容期间，回阻塞业务</u>

  > > > <u>Redis 通过增量式扩容解决了这个扩容期间业务无法访问的缺点</u>
  > > >
  > > > Redis默认初始化值为4

  > <u>`渐进式哈希`的精髓在于：数据的迁移不是一次性完成的，而是可以通过dictRehash()这个函数分步规划的</u>

  在迁移的过程中，数据是在新表还是旧表中并不是一个非常急迫的需求，迁移的过程并不会丢失数据，在旧表中找不到再到新表中寻找就是了（一般情况）

  遇到内存不足，然后ha切换 也会有问题。

  ##### 问题2  如果哈希函数设计不合理，哈希表在极端情况下会变成线性表.性能极低

  > *即使扩容以后他们的位置也不会变化，性能不会发生变化  .*

  *意思是说 ：根据 **负载因子** （总键值对数 / 箱子个数）  来调整扩容也无法解决哈希函数设计不*合理的问题

  旁白： 负载因子超过某个阈值时，出于链表性能的考虑，会进行Resize的操作

  > Java ：openjdk/jdk/src/share/classes/java/util/HashMap.java
  >
  > jdk 8 对于链表长度超过 8 的链表将转储为红黑树
  >
  > ![hashmap](https://img-blog.csdn.net/20171205200000196?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzUzMjY3MTg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
  >
  > Redis：经过严格测试，表现良好的默认哈希函数，避免了链表过长的问题，解决了这个缺点
  >



*有两个字典，分别存有 100 条数据和 10000 条数据，如果用一个不存在的 key 去查找数据，在哪个字典中速度更快？* 这个你不好回答了





#### 红黑树



##### 优点：

能够保证二叉树的插入和查找操作一直都是O(log(n))的时间复杂度（无最坏情况）





https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

| Algorithm  | **Average** | **Worst case** |
| ---------- | ----------- | -------------- |
| **Space**  | O(*n*）     | O(*n*）        |
| **Search** | O(log *n*)  | O(log *n*)     |
| **Insert** | O(log *n*)  | O(log *n*)     |
| **Delete** | O(log *n*)  | O(log *n*)     |



旁白：[理解时间复杂度O(log n)](https://github.com/wayou/wayou.github.io/issues/10)

如果有1000个记录，最多查找10次，1,000,000个记录，最多查找20次

![img](https://i.stack.imgur.com/4yiP0.jpg)

> > ![](https://images0.cnblogs.com/blog/175043/201412/151255023901167.png)
> >
> > > ##### 优点是占用内存小(没有多余的空节点，不会发生扩容等操作)
> > >
> > > 旁白：rb tree从众多平衡tree胜出，是因为 **功能、性能、空间开销的折中结果，最优**。

​       适合频繁更新，删除等操作。



##### 缺点：

随着n的变大（40w），map性能有下降（**纳秒级别，相差10倍**）也最够满足一般的业务了


![查找n(4..40w)](https://upload-images.jianshu.io/upload_images/1837968-1ae5f7e9f2656f95.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



- 数据查找 根据数据大小有关系。

  



## 2 黑盒测试



https://zhuanlan.zhihu.com/p/48066839

### 随机数据



#### 2.0 n=1千

map insert time: 0.623000 
map find time: 0.381000 
map erase time: 0.619000 
unordered_map insert time: 0.432000 
unordered_map find time: 0.148000 
unordered_map erase time: 0.246000 



### 2.1 10w 

> 10w量级的耗时，可以看出，map在增 删 查 三项上均**弱于unordered_map**，内存使用map略少



（why）????

```text
编译release版本：g++ -o3 -o main main.cpp
随机操作和顺序操作比例：1:1
```

10w量级的耗时，可以看出，map在增删查三项上均弱于unordered_map，内存使用map略少，但不明显：

```text
map insert time: 102.693000 
map find time: 69.264000 
map erase time: 96.144000 
unordered_map insert time: 43.258000 
unordered_map find time: 15.834000 
unordered_map erase time: 29.619000 

map内存：5096K
unordered_map内存：6712K
```

### 2.2 100w

> 100w量级的耗时，结论同上

（why）

```text
map insert time: 1462.718000 
map find time: 1161.637000 
map erase time: 1354.383000 
unordered_map insert time: 702.626000 
unordered_map find time: 328.684000 
unordered_map erase time: 448.539000 

map内存：47M
unordered_map内存：50M
```



 ###  类似数据

#### n=100

map insert time: 0.012000 
map find time: 0.010000 
map erase time: 0.019000 

unordered_map insert time: 0.034000 
unordered_map find time: 0.012000 
unordered_map erase time: 0.009000 



#### n=10w

map insert time: 52.211000 
map find time: 56.472000 
map erase time: 88.810000 

unordered_map insert time: 154.170000 
unordered_map find time: 89.057000 
unordered_map erase time: 48.600000



旁白

1. 精确到秒

   ```c
   time_t beg = time(0)
   ```

2. 精确到毫秒数

```c
clock_t begin , end;
begin = clock();
//这里是要统计时间的代码
end = clock();

unsigned uRunTime = (end - begin) * 1.0 / CLOCKS_PER_SEC * 1000;
```





STL map , nginx，linux 虚拟内存管理，他们都有红黑树的应用. 当你对搜索的效率要求较高，并且数据经常改动的情景，

你可以用红黑树, 也就是 map.

https://github.com/PeterRK/DSGO/blob/master/book/pages/08-A.md

### 总结

1. 单纯从测试数据看 unorder_map 性能优于map ，可以得出一个结论 前面性能就好吗？

有没有自己数据有问题，和测试场景有问题，o(1)-0(n)

数据太少并没有发现hash_table 缺点。

2. hash 在随机数据性能好于固定数据的。

3. 影响 HashMap 效率的主要是 哈希算法 和 内存分配算法,在哈希算法足够散列的情况下，预分配方式的效率更高

4. https://www.quora.com/What-is-the-Big-O-for-operations-in-a-Hashmap

5. ava 8 has a HashMap which degrades into a tree for collisions.

   This means it is O(1) typically and O(log N) in the worst case. 

## 3. 优化空间

- map 插入的后是有序数据，需要重载  bool operator < (const Foo & cmp) const 操作
- hash函数



谷歌的google:dense_hash_map耗时更少





![1547436431069](../images/1547436431069.png)

## 4. 什么时候用map，什么时候用hash_map?
分析角度 查找（命中 还是不命中）  插入 和存储空间 这三个方面

![map_02](../images/map_02.PNG)

![map_02](../images/map_01.PNG)





> When to choose unordered_map instead of map

- When you have good hasher and no memory limitation

>When to choose map instead of unordered_map
- When you need Low Memory:


- When you need guaranted Performance
    std::unordered_map  complexity O(1) ~~O(n) i
       std::map because it will give you guaranteed O(log N).







## 5 塔山

- https://zhuanlan.zhihu.com/p/37472912

- https://blog.csdn.net/a418382926/article/details/22302907

- https://www.youtube.com/watch?v=fHNmRkzxHWs

- https://my.oschina.net/hosee/blog/619618

- https://bestswifter.com/hashtable/

- https://blog.csdn.net/jasper_xulei/article/details/18364313 redis中几种哈希函数的研究

- https://caticat.github.io/2018/05/23/redis-algorithmic-hash/  redis中几种哈希函数的研究

- https://zhuanlan.zhihu.com/p/48066839 C++基础-map与unordered_map

- https://www.cnblogs.com/ontoweb-zp/p/10477039.html

- # [美团针对Redis Rehash机制的探索和实践](https://tech.meituan.com/2018/07/27/redis-rehash-practice-optimization.html)

- 数组+链表+红黑树的存储结构

- https://www.youtube.com/watch?v=c3RVW3KGIIE









#### 熟练度: 



![7da43dc67c70fee803071c83307c18a9](D:/doc/%E5%9B%BD%E7%BE%8E/doc/today/code/weekly/images/7da43dc67c70fee803071c83307c18a9.jpg)





> 目前处于第一想象 自己不知道，别人知道，该如何办呢？ 求讨论





扩展阅读：

压力测试：观察缺页中断情况

执行一次只有一个结果
ps -o majflt,minflt -p 1731

一直监控 知道手工终结
strace  -T -ttt -c  -p 1731 

pidstat - Report statistics for Linux tasks.

pidstat -r -p 1731  5

# 求指教

## 微信公共账号：

![qrcode__860](D:/doc/%E5%9B%BD%E7%BE%8E/doc/today/code/weekly/reading-notes/images/qrcode__860.jpg)

## 知识星球（付费的，不要加入 ）

![知识星球]()

# 第三天  IO

## 3.1 五大状态







![](https://pic1.zhimg.com/9faf605ebd46e68d125f5f5ed76495cc_r.jpg)



![](https://img-blog.csdn.net/20180624153134787?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0Nhb3lhbmdfSGU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## 3.2 epoll



```c++
int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
 select() can monitor only file descriptors numbers that are less than
       FD_SETSIZE，with FD_SETSIZE defined as 1024,

我们对于fd为6的可读事件感兴趣，那么r集合的第6个bit需要被设置为1。
这个系统调用会阻塞，直到我们感兴趣的事件（至少一个）发生。
调用返回时，内核同样使用这3个集合来存放fd实际发生的事件信息。也就是说，调用前这3个集合表示我们感兴趣的事件，调用后这3个集合表示实际发生的事件。

static __inline__ void __FD_SET(unsigned long fd, __kernel_fd_set *fdsetp)
{
    unsigned long _tmp = fd / __NFDBITS;
    unsigned long _rem = fd % __NFDBITS;
    fdsetp->fds_bits[_tmp] |= (1UL<<_rem); //右移
    0 -1024-2048
}
 
#define __NFDBITS    (8 * sizeof(unsigned long))
 
typedef struct {
    unsigned long fds_bits [__FDSET_LONGS];
} __kernel_fd_set;
 
#define __FDSET_LONGS   (__FD_SETSIZE/__NFDBITS)
 
#define __FD_SETSIZE    1024

```

#### 3.2 简单理解select模型

```
简单理解select模型
理解select模型的关键在于理解fd_set,为说明方便，取fd_set长度为1字节，fd_set中的每一bit可以对应一个文件描述符fd。则1字节长的fd_set最大可以对应8个fd。

（1）执行fd_set set; FD_ZERO(&set);则set用位表示是0000,0000。

（2）若fd＝5,执行FD_SET(fd,&set);后set变为0001,0000(第5位置为1)

（3）若再加入fd＝2，fd=1,则set变为0001,0011

（4）执行select(6,&set,0,0,0)阻塞等待

## （5）若fd=1,fd=2上都发生可读事件，则select返回，此时set变为0000,0011。注意：没有事件发生的fd=5被清空。
```





```c

int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
EPOLL_CTL_ADD：注册新的fd到epfd中；
EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
EPOLL_CTL_DEL：从epfd中删除一个fd
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);


struct epoll_event {
    uint32_t     events;    /* Epoll events */
    epoll_data_t data;      /* User data variable */
};

 typedef union epoll_data {
               void    *ptr;
               int      fd;//file
               uint32_t u32;
               uint64_t u64;
           } epoll_data_t;
EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；

EPOLLOUT：表示对应的文件描述符可以写；

EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；

EPOLLERR：表示对应的文件描述符发生错误；

EPOLLHUP：表示对应的文件描述符被挂断；

EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。

EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
--------------------- ！

```
https://zh.wikipedia.org/wiki/Epoll

### 3.4 总结

### 2） 为什么 select 慢

1. 从上面看，在第一次所有监听都没有事件时，调用 select 都需要把进程挂到所有监听的文件描述符一次。
2. 有事件到来时，不知道是哪些文件描述符有数据可以读写，需要把所有的文件描述符都轮询一遍才能知道。
3. 通知事件到来给用户进程，需要把整个 bitmap 拷到用户空间，让用户空间去查询。

上面的两种情况在监听的文件描述符较少的时候，性能损耗不太明显，但在百万连接的场景下，这种实现的缺点就会很明显。

### 3) 为什么epoll 快

这个会在下一篇博客来介绍一下，它是怎么规避这些问题的。

主要是几点:

1. 进程挂载到监听的文件描述符只会挂一次

2. 用专门的链表来存储有事件到来的文件描述符，返回给用户进程，只需要拷贝这个链表。

3. 使用红黑树来管理文件描述符，可以做到快速添加监听的文件描述符。

####  Reactor

If the Reactor pattern is used in an application with only one
thread of control it is possible to eliminate all synchronizatio

如果Reactor模式仅在具有一个的应用程序中使用
控制线程可以消除所有同步









```c++
由上图可知，在non-blocking IO中，虽然进程大部分时间都不会被block，但是它仍然要求进程去主动的check，并且当数据准备完成以后，也需要进程主动将数据拷贝到用户内存。I/O multiplexing中虽然在数据准备阶段和数据拷贝阶段会被block，由于其基于事件通知的，避免了持续check数据是否。


而asynchronous IO则完全不同。它就像是用户进程将整个IO操作交给了内核去完成，然后等待信号通知，用户进程不需要检查IO操作的状态，也不需要主动的去拷贝数据
--------------------- 
作者：wzgang123 
来源：CSDN 
原文：https://blog.csdn.net/wzgang123/article/details/51179776 
版权声明：本文为博主原创文章，转载请附上博文链接！
```

![**阻塞I/O模型**](https://images0.cnblogs.com/blog/468825/201403/082155544565666.png)



![image](https://images0.cnblogs.com/blog/468825/201403/082155571121722.png)

![image](https://images0.cnblogs.com/blog/468825/201403/082156006903861.png)



![](https://images0.cnblogs.com/blog/468825/201403/082156034098131.png)

![image](https://images0.cnblogs.com/blog/468825/201403/082156066597071.png)



### 3.3 同步I/O和异步I/O总结

https://songlee24.github.io/2016/07/19/explanation-of-5-IO-models/

POSIX把这两个术语定义如下:

- **同步I/O操作（synchronous I/O operation）导致请求进程阻塞，直到I/O操作完成。**

  A synchronous I/O operation causes the requesting process to be blocked until that I/O operation completes

- **异步I/O操作（asynchronous I/O operation）不导致请求进程阻塞。**

  An asynchronous I/O operation does not cause the requesting process to be blocked

![image](https://images0.cnblogs.com/blog/468825/201403/082156103464413.png)

# 求指教

## 微信公共账号：

![qrcode__860](../images/qrcode__860.jpg)

## 知识星球（付费的，不要加入 ）

![知识星球](../images/知识星球.jpg)



#### 参考 

https://blog.csdn.net/bboxhe/article/details/77367896

https://blog.csdn.net/zhougb3/article/details/79792089

https://blog.csdn.net/tianmohust/article/details/6595998

https://blog.csdn.net/stpeace/article/details/73717710





