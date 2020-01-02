# 资料

- https://app.yinxiang.com/shard/s39/res/d1ee9365-dfac-47c9-be7e-f36345ae67b2

- https://github.com/shichao-an/unpv13e

# 第二部分基本套接口编程



## 2

### 2.9





## 第六章 

# 



### 6.6 shutdown Function  

#### [Linux-socket的close和shutdown区别及应用场景](https://www.cnblogs.com/JohnABC/p/7238241.html)

多进程安全推荐使用shutdown，[调用shutdown与多线程、多进程无关](https://www.cnblogs.com/diegodu/p/4705806.html)。

需要考虑 与多进程 多线程有啥关系，引用计数。

### 6.8 TCP Echo Server (阻塞的)  

# 第三部分 高级套接口编程

## Chapter 14. Advanced I/O Functions  



- 14.3 recv and send Functions  

```c++
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
https://linux.die.net/man/2/recv
```

`MSG_WAITALL` *should* block until all data has been received

It tells the kernel not to return
from a read operation until the requested number of bytes have been read  



## Chapter 16. Nonblocking I/O  

中文：338页  英文 520页

### 16.1 Introduction（必看 ）

里面提到章节 

MSG_WAITALL flag (Figure 14.6)   Section 2.11   Section 2.6   