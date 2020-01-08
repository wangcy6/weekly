### 准备工作

- 下载代码

Unix-Network-Programming-Volume-1-The-Sockets-Networking-API-3rd-Edition

源码可以从http://www.unpbook.com/src.html下载得到。

解压之后的目录为unpv13e



- 学习环境搭建

https://www.cnblogs.com/xiehongfeng100/p/4593337.html

```shell

cd  unpv13e
Execute the following from the src/ directory:

    ./configure    # try to figure out all implementation differences

    cd lib         # build the basic library that all programs need
    make           # use "gmake" everywhere on BSD/OS systems

    cd ../libfree  # continue building the basic library
    make
   //则需要vim inet_ntop.c //将第60行的size_t size改成socklen_t size
    cd ../intro    # build and test a basic client program
    make daytimetcpcli
    ./daytimetcpcli 127.0.0.1
 


cp libunp.a /usr/lib 
cp libunp.a /usr/lib64 
cp unp.h /usr/include
cp config.h /usr/include 

```

- 具体例子 nonblock

server：tcpservselect03 9887

client：./tcpcli01 127.0.0.1 9877













### 第二部分基本套接口编程









### 第六章 Chapter 6. I/O Multiplexing  

# 



#### 6.6 shutdown Function  

#### [Linux-socket的close和shutdown区别及应用场景](https://www.cnblogs.com/JohnABC/p/7238241.html)

多进程安全推荐使用shutdown，[调用shutdown与多线程、多进程无关](https://www.cnblogs.com/diegodu/p/4705806.html)。

需要考虑 与多进程 多线程有啥关系，引用计数。

### 6.8 TCP Echo Server (阻塞的)  

### 第三部分 高级套接口编程

#### Chapter 14. Advanced I/O Functions  



- 14.3 recv and send Functions  

```c++
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
https://linux.die.net/man/2/recv
```

`MSG_WAITALL` *should* block until all data has been received

It tells the kernel not to return
from a read operation until the requested number of bytes have been read  



### Chapter 16. Nonblocking I/O  

中文：355 页  英文 520页  

### 16.1 Introduction（必看 ）

里面提到章节 

MSG_WAITALL flag (Figure 14.6)   Section 2.11   Section 2.6   

- short count 【send  EWOULDBLOCK   no room  】

> With a nonblocking TCP socket, if there is no room at all in the socket send buffer, we
> return immediately with an error of EWOULDBLOCK. 
>
> If there is some room in the socket
> send buffer, the return value will be the number of bytes the kernel was able to copy
> into the buffer. (This is called a short count.)  

- Section 13.4  Web client    