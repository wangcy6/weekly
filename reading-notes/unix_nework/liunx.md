



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





# 第二天 stl的map和hash使用场景

## 1. 区别

### 从时间复杂度

​	者对单次查询有时间要求的应用场景下，应使用map

> map是基于红黑树实现。红黑树作为一种自平衡二叉树，保障了良好的最坏情况运行时间，即它可以做到在O(log n)时间内完成查找，插入和删除，在对单次时间敏感的场景下比较建议使用map做为容器。比如实时应用，可以保证最坏情况的运行时间也在预期之内



https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

| Algorithm  | **Average** | **Worst case** |
| ---------- | ----------- | -------------- |
| **Space**  | O(*n*）     | O(*n*）        |
| **Search** | O(log *n*)  | O(log *n*)     |
| **Insert** | O(log *n*)  | O(log *n*)     |
| **Delete** | O(log *n*)  | O(log *n*)     |



### 从空间来看：



其余情况应使用unordered_map

> unordered_map是基于hash_table实现，一般是由一个大vector，vector元素节点可挂接链表来解决冲突来实现。hash_table最大的优点，就是把数据的存储和查找消耗的时间大大降低，几乎可以看成是常数时间；

而代价仅仅是消耗比较多的内存。然而在当前可利用内存越来越多的情况下，用空间换时间的做法是值得的。

https://en.wikipedia.org/wiki/Hash_table







数据是否有序：



在需要有序性，map有限

### 优缺点

#### hash:

- 优点：

  ​	Hash表，在完全随机/无冲突 的情况下，插入、查询和删除都可以认为是O(1)的时间复杂度，最完美

    

  | Algorithm  | **Average** | **Worst case** |
  | ---------- | ----------- | -------------- |
  | **Space**  | O(*n*）     | O(*n*）        |
  | **Search** | O(1)        | O(*n*）        |
  | **Insert** | O(1)        | O(*n*）        |
  | **Delete** | O(1)        | O(*n*)         |

  ![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg/1280px-Hash_table_3_1_1_0_1_0_0_SP.svg.png)

- 缺点： .

  链地址法冲突的缺点

  

  问题1  哈希表扩容的过程，以及对查找性能的影响

  > Redis 通过增量式扩容解决了这个缺点

  

  

  问题2  如果哈希函数设计不合理，哈希表在极端情况下会变成线性表.性能极低

  ​            即使扩容以后他们的位置也不会变化

  > Java 的长处在于当哈希函数不合理导致链表过长时，会使用红黑树来保证插入和查找的效率
  >
  > Redis 经过严格测试，表现良好的默认哈希函数，避免了链表过长的问题
  >
  > 没有完美的架构，只有满足需求的架构



#### 红黑树

- 优点：

  能够保证二叉树的插入和查找操作一直都是O(log(n))的时间复杂度（无坏情况）

  所有的元素在树中是排序好的。

  RB-Tree是**功能、性能、空间开销的折中结果**。

  

- 缺点：

  











## 2 测试查找



####  随着数据量的增多

https://zhuanlan.zhihu.com/p/48066839



![查找n(4..40w)](https://upload-images.jianshu.io/upload_images/1837968-1ae5f7e9f2656f95.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2.1 10w

> 10w量级的耗时，可以看出，map在增 删 查 三项上均**弱于unordered_map**，内存使用map略少



（why）????

```text
编译release版本：g++ -o3 -o main main.cpp
随机操作和顺序操作比例：1:1
```

10w量级的耗时，可以看出，map在增删查三项上均弱于unordered_map，内存使用map略少，但不明显：

```text
map insert time: 71.064000
map find time: 30.305000
map erase time: 45.373000

unordered_map insert time: 42.139000
unordered_map find time: 11.316000
unordered_map erase time: 31.453000

map内存：5096K
unordered_map内存：6712K
```

### 2.2 100w

> 100w量级的耗时，结论同上

（why）????

```text
map insert time: 955.625000
map find time: 574.289000
map erase time: 623.460000
unordered_map insert time: 575.636000
unordered_map find time: 166.449000
unordered_map erase time: 294.509000

map内存：47M
unordered_map内存：50M
```



 

### 2.3 测试 插入和删除操作



 hash_map（10万） map（10万） hash_map（20万） map（20万） hash_map（30万） map（30万） 
添加：   93 （少)    47 |  156   94(少)  | 203   172（map 少）
删除： 8422   32（map 少） | 33765   63 (map 少)| 76016   78（map 少）

>map在频繁的删除和插入方面 耗时更少。



STL map , nginx，linux 虚拟内存管理，他们都有红黑树的应用. 当你对搜索的效率要求较高，并且数据经常改动的情景，你可以用红黑树, 也就是 map.

https://github.com/PeterRK/DSGO/blob/master/book/pages/08-A.md

## 3. 优化空间

- map 插入的后是有序数据，需要重载  bool operator < (const Foo & cmp) const 操作
- hash函数和空间的利用（这个是重点！！）



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
- https://blog.csdn.net/a418382926/article/details/22302907
- https://www.youtube.com/watch?v=fHNmRkzxHWs
- https://my.oschina.net/hosee/blog/619618
- https://bestswifter.com/hashtable/
- https://blog.csdn.net/jasper_xulei/article/details/18364313 redis中几种哈希函数的研究
- https://caticat.github.io/2018/05/23/redis-algorithmic-hash/  redis中几种哈希函数的研究
- https://zhuanlan.zhihu.com/p/48066839 C++基础-map与unordered_map









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

## 第三天  IO

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
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

 typedef union epoll_data {
               void    *ptr;
               int      fd;//file
               uint32_t u32;
               uint64_t u64;
           } epoll_data_t;

           struct epoll_event {
               uint32_t     events;    /* Epoll events */
               epoll_data_t data;      /* User data variable */
           };

```

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





