---
title: "FQA_Linux"
date: 2019-11-12
description: "FQA"
draft: false
categories: ["Linux"]
---

# 知识卡

![image.png](https://i.loli.net/2019/11/13/iBAcurKQygeSUTD.png)



# 一、基础





## 1、进程vs线程

### 问1 ：进程间通信方式

> 进程间通信 2个情况 
>
> 第一个是    exchange data  传递数据 （跨主机 TPC，不跨主机 IPC）
>
> 第二个是  synchronize  同步(内核，非内核的) 信号灯



#### 最常用的socket（TCP/UDP）



#### 信号

一、 问：有哪2个**信号**不能**被忽略**？



答：

1. 什么是信号：

 软中断信号（signal，又简称为信号）用来通知进程发生了异步事件 

 信号是进程间通信机制中**唯一**的异步通信机制，一个进程不必通过任何操作来**等待**信号的到达 



```
 信号与中断的区别：
（1）中断有优先级，而信号没有优先级，所有的信号都是平等的；

（2）信号处理程序是在用户态下运行的，而中断处理程序是在核心态下运行；

（3）中断响应是及时的，而信号响应通常都有较大的时间延迟。 
```





操作系统不会为了处理一个信号而把当前正在运行的进程挂起，因为这样的话资源消耗太大了，如果不是紧急信号，是不会立即处理的，操作系统多选择**在内核态切换回用户态的时候处理信号**。

因为进程有可能在睡眠的时候收到信号，操作系统肯定不愿意切换当前正在运行的进程，于是就得把信号储存在进程唯一的 PCB(task_struct) 当中。



2. [信号什么发生的？](http://kernel.meizu.com/linux-signal.html)



理解信号异步机制的关键是信号的响应时机，我们对一个进程发送一个信号以后，其实并没有硬中断发生，只是简单把信号挂载到目标进程的信号 pending 队列上去，信号真正得到执行的时机是进程执行完异常/中断返回到用户态的时刻。

让信号看起来是一个异步中断的关键就是，正常的用户进程是会频繁的在用户态和内核态之间切换的（这种切换包括：系统调用、缺页异常、系统中断…），所以信号能很快的能得到执行。

但这也带来了一点问题，内核进程是不响应信号的，除非它刻意的去查询。

所以通常情况下我们无法通过kill命令去杀死一个内核进程。

 ![img](http://kernel.meizu.com/images/posts/2016/07/signal_ret_to_user.png) 

![信号处理实际](https://i.loli.net/2019/11/12/MBIDfW9HOJ4KoZG.png)

3. **被忽略** 进程对信号的三种响应方式之一

- 忽略信号
  - 不采取任何操作、有两个信号不能被忽略：SIGKILL和SIGSTOP。
- 捕获并处理信号
  - 内核中断正在执行的代码，转去执行先前注册过的处理程序。
- 执行默认操作
  - 默认操作通常是终止进程，这取决于被发送的信号。

> 其中`SIGKILL`和`SIGSTOP`信号不能被捕获、阻塞或忽略。  还是没有理解  不能被捕获

 

 kill -s SIGKILL

这个强大和危险的命令迫使进程在运行时突然终止，

进程在结束后不能自我清理。危害是导致系统资源无法正常释放，一般不推荐使用，除非其他办法都无效。 

![终止](https://i.loli.net/2019/11/12/Wi1hpb7ZQC6Vqay.png)





#### 同步



![image.png](https://i.loli.net/2019/11/13/ZI1aoBWjLmMykzY.png)

![image.png](https://i.loli.net/2019/11/13/6vzlwaTFo32kdfE.png)



### 线程

### 一. 问2 线程同步方式？

> 线程并发2个方式 消息传递，共享对象



答：



- 锁

  互斥锁

  条件变量

  读写锁（不推荐）

  自旋锁

  高级组件

  #### 问 rwlock和mutex有什么不同和优劣呢

## 2、文件系统

### 问2 一次write操作，数据写入内存那个部分？



![image.png](https://i.loli.net/2019/11/12/JoQmkNVMSRAG7U9.png)



#### 一.  write文件有那2个方式呀？

> 我的理解：还用问吗？直接wirte，还有什么方式

###### mmap也被称为zero-copy技术 





[内存映射文件](https://zh.wikipedia.org/wiki/%E5%86%85%E5%AD%98%E6%98%A0%E5%B0%84%E6%96%87%E4%BB%B6) 

 Memory-mapped I/O uses the same [address space](https://en.wikipedia.org/wiki/Address_space) to address both [memory](https://en.wikipedia.org/wiki/Computer_memory) and [I/O devices](https://en.wikipedia.org/wiki/I/O_device). The memory and [registers](https://en.wikipedia.org/wiki/Register_(computing)) of the I/O devices are mapped to (associated with) address values. So when an address is accessed by the CPU, it may refer to a portion of [physical RAM](https://en.wikipedia.org/wiki/Physical_memory), or it can instead refer to memory of the I/O device. 





> SQLite:
>
> Beginning with [version 3.7.17](https://www.sqlite.org/releaselog/3_7_17.html) (2013-05-20), SQLite has the option of accessing disk content directly using memory-mapped I/O and the new xFetch() and xUnfetch() methods on [sqlite3_io_methods](https://www.sqlite.org/c3ref/io_methods.html). 
>
>  https://www.sqlite.org/mmap.html 



![image.png](https://i.loli.net/2019/11/13/zQbogWE5VYj7U2N.png)

> MongoDB
>
> The main storage engine in MongoDB is the Memory Mapped Storage Engine or MMAP for short. 
>
> The MMAP storage engine uses memory mapped files as its storage engine. 
>
>  http://learnmongodbthehardway.com/schema/mmap/ 
>
>  Memory mapped files allow MongoDB to delegate the handling of Virtual Memory to the operating system instead of explicitly managing memory itself. 



 mmap系统调用并不是完全为了用于共享内存而设计的。

它本身提供了不同于一般对普通文件的访问方式，进程可以像读写内存一样对普通文件的操作 

 **常规文件操作需要从磁盘到页缓存再到用户主存的两次数据拷贝。**

**而mmap操控文件，只需要从磁盘到用户主存的一次数据拷贝过程。** 

~~~CQL
由上文讨论可知，mmap优点共有一下几点：

1、对文件的读取操作跨过了页缓存，减少了数据的拷贝次数，用内存读写取代I/O读写，提高了文件读取效率。

2、实现了用户空间和内核空间的高效交互方式。两空间的各自修改操作可以直接反映在映射的区域内，从而被对方空间及时捕捉。

3、提供进程间共享内存及相互通信的方式。不管是父子进程还是无亲缘关系的进程，都可以将自身用户空间映射到同一个文件或匿名映射到同一片区域。从而通过各自对映射区域的改动，达到进程间通信和进程间共享的目的。

     同时，如果进程A和进程B都映射了区域C，当A第一次读取C时通过缺页从磁盘复制文件页到内存中；但当B再读C的相同页面时，虽然也会产生缺页异常，但是不再需要从磁盘中复制文件过来，而可直接使用已经保存在内存中的文件数据。

4、可用于实现高效的大规模数据传输。内存空间不足，是制约大数据操作的一个方面，解决方案往往是借助硬盘空间协助操作，补充内存的不足。但是进一步会造成大量的文件I/O操作，极大影响效率。这个问题可以通过mmap映射很好的解决。换句话说，但凡是需要用磁盘空间代替内存的时候，mmap都可以发挥其功效
~~~



##### 文件读写基本流程



~~~c
读文件

1、进程调用库函数向内核发起读文件请求；

2、内核通过检查进程的文件描述符定位到虚拟文件系统的已打开文件列表表项；

3、调用该文件可用的系统调用函数read()

3、read()函数通过文件表项链接到目录项模块，根据传入的文件路径，在目录项模块中检索，找到该文件的inode；

4、在inode中，通过文件内容偏移量计算出要读取的页；

5、通过inode找到文件对应的address_space；

6、在address_space中访问该文件的页缓存树，查找对应的页缓存结点：

（1）如果页缓存命中，那么直接返回文件内容；

（2）如果页缓存缺失，那么产生一个页缺失异常，创建一个页缓存页，同时通过inode找到文件该页的磁盘地址，读取相应的页填充该缓存页；重新进行第6步查找页缓存；

7、文件内容读取成功。

 

**写文件**

前5步和读文件一致，在address_space中查询对应页的页缓存是否存在：

6、如果页缓存命中，直接把文件内容修改更新在页缓存的页中。写文件就结束了。这时候文件修改位于页缓存，并没有写回到磁盘文件中去。

7、如果页缓存缺失，那么产生一个页缺失异常，创建一个页缓存页，同时通过inode找到文件该页的磁盘地址，读取相应的页填充该缓存页。此时缓存页命中，进行第6步。

8、一个页缓存中的页如果被修改，那么会被标记成脏页。脏页需要写回到磁盘中的文件块。有两种方式可以把脏页写回磁盘：

（1）手动调用sync()或者fsync()系统调用把脏页写回

（2）pdflush进程会定时把脏页写回到磁盘

同时注意，脏页不能被置换出内存，如果脏页正在被写回，那么会被设置写回标记，这时候该页就被上锁，其他写请求被阻塞直到锁释放。
~~~

## 3 、 网络模块



#### 问题3 为什么采用epoll？

- 第一步： 同步与阻塞，异步和非阻塞的区别？
- 第二步：了解网络模型
- 检查：select/epoll 是阻塞（ Block ）还是非阻塞（ Unblock ），同步( (Sync) )还是异步 (Async) ?
- 第三步：epoll特点
- 第四步：为什么不用现有框架呢 ，自己写干什么

  



第一步： 同步与阻塞，异步和非阻塞的区别？

- 别人的答案

~~~ c
IO操作其实可以分成两个步骤，请求IO操作和执行IO操作。
一般的IO调用过程是这样的：发起IO操作的请求，执行IO操作，得到IO操作的结果，将结果返回给IO操作请求。

同步和异步同步和异步是一种通信机制，涉及到调用方和被调用方，关注的是IO操作的执行过程及结果的返回方式，不同点在于双方在这两个方面的行为方式。
如果调用方需要保持等待直到IO操作完成进而通过返回获得结果，则是同步的；
如果调用方在IO操作的执行过程中不需要保持等待，而是在操作完成后被动的接受（通过消息或回调）被调用方推送的结果，则是异步的。

同步和异步，适合描述执行IO操作的情境。

 阻塞和非阻塞阻塞和非阻塞是一种调用机制，只涉及到调用方，
关注的是IO操作的执行状态，不同点在于请求IO操作后，针对IO操作的状态，调用方的行为方式。

如果调用方等待IO操作完成后返回，则是阻塞的；
如果调用方不需要等待IO操作完成就立即返回，则是非阻塞的，非阻塞的情况下，常常需要多次调用去check，才能获得IO操作的结果。
阻塞和非阻塞，适合描述发起IO操作请求的情境。

作者：Ownbin
链接：https://www.zhihu.com/question/19732473/answer/79784104
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
~~~





从操作系统角度考虑 只有AIO，操作才是真正异步

从用户角度  Libevent ,Netty ,确实IO多路复用也是异步的 如何理解？



> **libevent** is a [software library](https://en.wikipedia.org/wiki/Software_library) that provides asynchronous event notification.
>
>  The libevent [API](https://en.wikipedia.org/wiki/API) provides a mechanism to execute a [callback](https://en.wikipedia.org/wiki/Callback_(computer_science)) function when a specific event occurs on a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) or after a [timeout](https://en.wikipedia.org/wiki/Timeout_(telecommunication)) has been reached. libevent also supports callbacks triggered by [signals](https://en.wikipedia.org/wiki/Signal_(computing)) and regular timeouts.
>
> Netty is *an asynchronous event-driven network application framework*
> for rapid development of maintainable high performance protocol servers & clients. 

![image.png](https://i.loli.net/2019/11/14/4lPTmeKIc7syv1r.png)

![image.png](https://i.loli.net/2019/11/14/G1ytqCYJOuFXZ9S.png)

###### 第二步：了解网络模型



![image.png](https://i.loli.net/2019/11/14/lgiGow23cjHxMZz.png)

 假设你即将要为一个重要的大公司开发一个新的关键任务的应用程序。

在第一次会议上，你了解到这个系统必须能无性能损耗地扩展到支持15万个并发用户。这时所有的人都看着你，你会说什么？ 

 



NIO（Non-blocking I/O，在Java领域，也称为New I/O），是一种同步非阻塞的I/O模型，也是I/O多路复用的基础，已经被越来越多地应用到大型应用服务器，成为解决高并发与大量连接、I/O处理问题的有效方式 

###### 检查：select/epoll 是阻塞（ Block ）还是非阻塞（ Unblock ），同步( (Sync) )还是异步 (Async) ?

###### 第三步：epoll特点





```c

```

epoll 

-  很容易**扩展到**监控大量socket连接

  > scales well to large numbers of  watched file descriptors.

- 大量连接部分活跃情况有优势，比select多了一层异步回调。

   几个线程处理上万连接，主要是指有很多不忙的连接的场景，如聊天室服务器

- 单个连接业务处理不能做长时间阻塞操作



- select低效是因为每次它都需要轮询。但低效也是相对的，视情况而定，也可通过良好的设计改善 

  









```c
epoll_wait(2) waits for I/O events, blocking the calling thread if no events are currently available.
    
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
The call will block until either:、
 *  a file descriptor delivers an event;
  Q7  If more than one event occurs between epoll_wait(2) calls, are they combined or reported separately?
 A7  They will be combined.
*  the call is interrupted by a signal handler; or
 *  the timeout expires.
    
不要说et模式一定采用break方式读取了
    
    
    9.  Do I need to continuously read/write a file descriptor until
           EAGAIN when using the EPOLLET flag (edge-triggered behavior)?

           Receiving an event from epoll_wait(2) should suggest to you that
           such file descriptor is ready for the requested I/O operation.
           You must consider it ready until the next (nonblocking)
           read/write yields EAGAIN.  When and how you will use the file
           descriptor is entirely up to you.

           For packet/token-oriented files (e.g., datagram socket, terminal
           in canonical mode), the only way to detect the end of the
           read/write I/O space is to continue to read/write until EAGAIN.

           For stream-oriented files (e.g., pipe, FIFO, stream socket), the
           condition that the read/write I/O space is exhausted can also be
           detected by checking the amount of data read from / written to
           the target file descriptor.  For example, if you call read(2) by
           asking to read a certain amount of data and read(2) returns a
           lower number of bytes, you can be sure of having exhausted the
           read I/O space for the file descriptor.  The same is true when
           writing using write(2).  (Avoid this latter technique if you can‐
           not guarantee that the monitored file descriptor always refers to
           a stream-oriented file.)

     Epoll is relatively young. It was created by Davide Libenzi in 2002. 
     For comparison: Windows did IOCP in 1994 and FreeBSD's kqueue was introduced in July 2000. 
 Unfortunately, even though epoll is the youngest in the advanced IO multiplexing family, it's the worse in the bunch.  
         EPOLLONESHOT https://www.cnblogs.com/kex1n/p/7451069.html
所以在处理数据时，不需要在RECV时不断的循环去读一直读到EAGAIN，但如果设置了EPOLLONESHOT后
    
    
  因为 LT & ET 触发方式不同，处理事件的逻辑也不同。先看 manpage 里面的一个例子

1. The file descriptor that represents the read side of a pipe (rfd) is registered on the epoll instance.

2. A pipe writer writes 2 kB of data on the write side of the pipe.

3. A call to epoll_wait(2) is done that will return rfd as a ready file descriptor.

4. The pipe reader reads 1 kB of data from rfd.

5. A call to epoll_wait(2) is done.
在 ET 模式下，这种情况可能导致进程一直阻塞。

假设 pipe 刚开始是空的，A端发送 2KB，然后等待B端的响应。
步骤2完成后，缓冲区从空变成非空，ET 会触发 EPOLLIN 事件
步骤3 epoll_wait 正常返回
B开始读操作，但是只从管道读 1KB 数据
步骤5调用 epoll_wait 将一直阻塞。因为 ET 下，缓冲区从空变成非空，才会触发 EPOLLIN 事件，缓冲区从满变成非满，才会触发 EPOLLOUT 事件。而当前情况不满足任何触发条件，所以 epoll_wait 会一直阻塞。
```
[man epoll](http://man7.org/linux/man-pages/man7/epoll.7.html)





第四步：为什么不用现有框架呢 ，自己写干什么



### 问题4  tcp 



#### 问：如何消除大量time_wait 状态？



回答：



对于服务器来说 一般属于被动关闭一方，一般不会出现多time_wait 状态，并且TCP建立连接，只会消耗更多文件，内存等资源 并不过占用过多的port端口？



画外音：

>  作为客户端，最多可以 使用64512个端口，也就是同一时刻对同一个服务器同一个端口可以创建64512个TCP连接 
>
> 而对于服务器来说，它没有所谓的“65536”端口数量的限制。可以有多少客户端连接服务器，取决于CPU、内存等资源的大小 
>
> 一个TCP连接唯一性确定：
>
> ServerIP => ServerPort <= TCP => ClientIP => ClientPort 

分析一下是什么原因造成的呢？



- 客户端大量的压测  每秒就会创建400+的连接，1分钟就是2.4万的连接，系统无法及时回收 

默认ip_local_port_range是2.8w个





###### 解决方式是：



- 当出现大量的time_wait状态时候，首先检查一下当前系统配置参数情况，如果在合理访问内 

具体参数是：

`1.随机端口范围 ip_local_port_range  默认2.8w`

`sysctl -a | grep  ip_local_port_range`
`net.ipv4.ip_local_port_range = 32768    61000`

2. `系统允许的文件描述符数量 默认6.5w可以调整10w`

 `cat /proc/sys/fs/file-max`
`655360`

3. `心跳检查参数`

`sysctl -a | grep  tcp_keepalive_time`
`net.ipv4.tcp_keepalive_time = 7200` 



- `tcp_tw_reuse等快速回收 参数 是有风险的不建议启用。`

**TIME_WAIT关闭的危害：**

1、 网络情况不好时，如果主动方无TIME_WAIT等待，关闭前个连接后，主动方与被动方又建立起新的TCP连接，这时被动方重传或延时过来的FIN包过来后会直接影响新的TCP连接；

2、 同样网络情况不好并且无TIME_WAIT等待，关闭连接后无新连接，当接收到被动方重传或延迟的FIN包后，会给被动方回一个RST包，可能会影响被动方其它的服务连接。







~~~shell
ulimit -a

vim /etc/sysctl.conf 
net.ipv4.tcp_tw_reuse = **1 表示开启重用**。允许将TIME-WAIT sockets重新用于新的TCP连接，默认为0，表示关闭；

net.ipv4.tcp_tw_recycle = 1 表示开启TCP连接中TIME-WAIT sockets的快速回收，默认为0，表示关闭。

netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'

sysctl -a | grep time | grep wait
net.netfilter.nf_conntrack_tcp_timeout_close_wait = 60
net.netfilter.nf_conntrack_tcp_timeout_fin_wait = 120
net.netfilter.nf_conntrack_tcp_timeout_time_wait = 120


更多参数
[root@aaa1 ~]# vim /etc/sysctl.conf

增加以下几行：（请根据实际需要添加）

net.ipv4.tcp_fin_timeout = 30

net.ipv4.tcp_keepalive_time = 1200

net.ipv4.tcp_syncookies = 1

net.ipv4.tcp_tw_reuse = 1

net.ipv4.tcp_tw_recycle = 1

net.ipv4.ip_local_port_range = 1024 65000

net.ipv4.tcp_max_syn_backlog = 8192

net.ipv4.tcp_max_tw_buckets = 5000

说明：

net.ipv4.tcp_syncookies = 1 表示开启SYN Cookies。当出现SYN等待队列溢出时，启用cookies来处理，可防范少量SYN攻击，默认为0，表示关闭；

net.ipv4.tcp_tw_reuse = 1 表示开启重用。允许将TIME-WAIT sockets重新用于新的TCP连接，默认为0，表示关闭；

net.ipv4.tcp_tw_recycle = 1 表示开启TCP连接中TIME-WAIT sockets的快速回收，默认为0，表示关闭。

net.ipv4.tcp_fin_timeout = 30 表示如果套接字由本端要求关闭，这个参数决定了它保持在FIN-WAIT-2状态的时间。

net.ipv4.tcp_keepalive_time = 1200 表示当keepalive起用的时候，TCP发送keepalive消息的频度。缺省是2小时，改为20分钟。

net.ipv4.ip_local_port_range = 1024 65000 表示用于向外连接的端口范围。缺省情况下很小：32768到61000，改为1024到65000。

net.ipv4.tcp_max_syn_backlog = 8192 表示SYN队列的长度，默认为1024，加大队列长度为8192，可以容纳更多等待连接的网络连接数。

net.ipv4.tcp_max_tw_buckets = 5000表示系统同时保持TIME_WAIT套接字的最大数量，如果超过这个数字，TIME_WAIT套接字将立刻被清除并打印警告信息。默认为180000，改为5000。对于Apache、Nginx等服务器，上几行的参数可以很好地减少TIME_WAIT套接字数量，但是对于Squid，效果却不大。此项参数可以控制TIME_WAIT套接字的最大数量，避免Squid服务器被大量的TIME_WAIT套接字拖死。


/etc/sysctl.conf
sysctl -w fs.file-max=10485760 #系统允许的文件描述符数量10m
sysctl -w net.ipv4.tcp_rmem=1024 #每个tcp连接的读取缓冲区1k，一个连接1k
sysctl -w net.ipv4.tcp_wmem=1024 #每个tcp连接的写入缓冲区1k
#修改默认的本地端口范围
sysctl -w net.ipv4.ip_local_port_range='1024 65535'
sysctl -w net.ipv4.tcp_tw_recycle=1  #快速回收time_wait的连接
sysctl -w net.ipv4.tcp_tw_reuse=1
sysctl -w net.ipv4.tcp_timestamps=1
#用户单进程的最大文件数，用户登录时生效
echo '* soft nofile 1048576' >> /etc/security/limits.conf
echo '* hard nofile 1048576' >> /etc/security/limits.conf
ulimit -n 1048576 #用户单进程的最大文件描述符数 当前会话生效

TIME_WAIT状态存在的理由：
1）可靠地实现TCP全双工连接的终止
   在进行关闭连接四次挥手协议时，最后的ACK是由主动关闭端发出的，如果这个最终的ACK丢失，服务器将重发最终的FIN，
因此客户端必须维护状态信息允许它重发最终的ACK。如果不维持这个状态信息，那么客户端将响应RST分节，服务器将此分节解释成一个错误（在java中会抛出connection reset的SocketException)。
因而，要实现TCP全双工连接的正常终止，必须处理终止序列四个分节中任何一个分节的丢失情况，主动关闭的客户端必须维持状态信息进入TIME_WAIT状态。
 
2）允许老的重复分节在网络中消逝 
TCP分节可能由于路由器异常而“迷途”，在迷途期间，TCP发送端可能因确认超时而重发这个分节，迷途的分节在路由器修复后也会被送到最终目的地，这个原来的迷途分节就称为lost duplicate。
在关闭一个TCP连接后，马上又重新建立起一个相同的IP地址和端口之间的TCP连接，后一个连接被称为前一个连接的化身（incarnation)，那么有可能出现这种情况，前一个连接的迷途重复分组在前一个连接终止后出现，从而被误解成从属于新的化身。
为了避免这个情况，TCP不允许处于TIME_WAIT状态的连接启动一个新的化身，因为TIME_WAIT状态持续2MSL，就可以保证当成功建立一个TCP连接的时候，来自连接先前化身的重复分组已经在网络中消逝。
~~~

参考：[百万并发连接、65536和Linux TCP/IP 性能优化](https://pathbox.github.io/2018/02/06/65535-port-and-concurrent-socket/)





# 二、提升

  

## 性能优化

### 问题4 如果一个c++开发的系统，在生产运行3年后，最后查询越来越慢 如何解决？

  > c++ 语言本身 ；和操作系统方面
  >
  > 参考书
  >
  >   性能之巅 洞悉系统、企业与云计算   
  >
  >  提高C++性能的编程技术
  >
  >  C++性能优化指南
  >
  > 参考项目：
  >
  > 虽然很重要但是不考虑问题
  >
  > 优化数据库，这个和程序有啥关系

  

  #### 回答1  热点函数优化 20%原则

  - 能不能内敛

  - 函数 时间复杂度  减少循环的层次，次数和 循环体非必要函数调用出现的开销（引用避免拷贝）

  - 函数调用开销  

     虚函数的另一个问题是编译器难以内联它们 

     用模板在编译时选择实现  

     std:bind+std:function取代虚函

    [Effective C++ 35：考虑虚函数的其他替代设计](https://mp.weixin.qq.com/s/a-vS5iijogedgXzebAfGnw)

    

    编译选项 o2
    
    提高编译速度
    
    
    
    

  #### 回答2 优化数据结构，更好的库

  

  

  

  

### 参考资料



[1]  http://kernel.pursuitofcloud.org/531016 

[2]  https://www.kancloud.cn/kancloud/understanding-linux-processes/52197 

[3] [从内核文件系统看文件读写过程](https://www.cnblogs.com/huxiao-tee/p/4657851.html) [ok]

[4] [认真分析mmap：是什么 为什么 怎么用](https://www.cnblogs.com/huxiao-tee/p/4660352.html) 

[5] [Linux 中 mmap() 函数的内存映射问题理解？](https://www.zhihu.com/question/48161206) [这个很重要，必看]

[6] [Mongodb源码分析--内存文件映射(MMAP)](https://www.cnblogs.com/daizhj/archive/2011/04/25/mongos_mmap_source_code.html)

[7] [MMAP storage Engine in Mongodb](https://stackoverflow.com/questions/29575420/mmap-storage-engine-in-mongodb)

[8]  https://juejin.im/post/5aeb0e016fb9a07ab7740d90 深入理解读写锁ReentrantReadWriteLock

​     http://blog.guoyb.com/2018/02/11/rwlock/ 

​     https://tech.meituan.com/2018/11/15/java-lock.html 

【9】 获取自旋锁和禁止中断的时候为什么不能睡眠? 

​       https://www.zhihu.com/question/28821201 

​      https://www.zhihu.com/question/23995948 

   https://segmentfault.com/a/1190000019506505 



[10] 网络编程：进程间通信性能比较  https://zhuanlan.zhihu.com/p/80368714 

[11] https://people.cs.clemson.edu/~dhouse/courses/405/papers/optimize.pdf 

[12]  http://oldblog.antirez.com/post/redis-virtual-memory-story.html 

[13]  https://www.sqlite.org/mmap.html 

[14] What are the advantages and disadvantages of memory-mapped I/O and direct (or port) I/O?

【15】 [Java NIO浅析](https://tech.meituan.com/2016/11/04/nio.html)

[16] [socket阻塞与非阻塞，同步与异步、I/O模型，select与poll、epoll比较](https://www.cnblogs.com/wujing-hubei/p/6111347.html)

[17] [Blocking I/O, Nonblocking I/O, And Epoll](https://eklitzke.org/blocking-io-nonblocking-io-and-epoll) 【redis作者]

【18】[浅谈IO的多路复用技术之一(select和epoll实质)](https://mp.weixin.qq.com/s?src=3&timestamp=1573703798&ver=1&signature=WJm9uHtBrHURp7Oi0fj0HIHf6DqrXluIt6pEncwUr1MJxomfqcbI8WZbF8*AvjKN0u*09abygHHHqDxYIIPXSdRMmr78pQuYAFtDOx4KQbr4Tg-iQ8Twfc-Kw9bFRFoawB*HBoIDqenYqwD2EHGtGA==)

​      https://medium.com/@copyconstruct/the-method-to-epolls-madness-d9d2d6378642 













  重入

