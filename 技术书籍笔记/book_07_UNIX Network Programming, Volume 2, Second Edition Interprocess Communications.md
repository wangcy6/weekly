---
title: "unix网络编程-卷2-进程间通"
date: 2020-03-04
description: ""
draft: false
tags: ["book","unix网络编程-卷2-进程间通"]
categories: ["liunx"]

 
---

> UNIX Network Programming, Volume 2, Second Edition: Interprocess Communications

# day1

### 源代码编译(45分钟)



#### 1 下载源码:

W. Richard Stevens 的主页：http://www.kohala.com/start/

```
cd /root/bin
wget http://www.kohala.com/start/unpv22e/unpv22e.tar.gz 
```

#### 2 解压

```
cd /root/bin
tar xvf unpv22e.tar.gz 
```



#### 3 编译库文件，及修改头文件

```
cd /root/bin/unpv22e/
./configure
```

#### 3.1 修改生成 config.h 文件，注释以下几行

```
vi config.h
56 // #define uint8_t unsigned char
57 // #define uint16_t unsigned short
58 // #define uint32_t unsigned int
```

#### 3.2 添加 MSG_R 和 MSG_W 定义

```
vi config.h
67 typedef unsigned long ulong_t;
68 #define MSG_R 0400
69 #define MSG_W 0200
```

#### 3.3 添加_GNU_SOURCE 定义

```
vi config.h
#define _GNU_SOURCE
```

#### 3.4 创建 warpunix.c，使用 mkstemp 函数替换 mktemp 函数

```
cd lib
 void
 Mktemp(char *template)
 {
 if (mkstemp(template) == NULL || template[0] == 0)
 err_quit("mktemp error");
1}
```

#### 3.5 编译生成 libunpipc.a

```
cd lib
make
```

#### 4 构建自己的编写代码的目录









## 参考



[https://ubin.top/2016/01/22/UNIX%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B-%E5%8D%B72-%E6%BA%90%E4%BB%A3%E7%A0%81%E7%BC%96%E8%AF%91/](https://ubin.top/2016/01/22/UNIX网络编程-卷2-源代码编译/)

  

# day2

### 锁



- 互斥锁：陷入阻塞后，是无法确定，什么时候能再次获取锁，有可能无限等待。无法事件通知

- 条件变量： while判断条件是否满足，不然 pthread_cond_wait ,pthread_cond_signal 分开的

  - 条件不不满，也不长期占用锁

  

### 读写锁(40分钟)

- 使用互斥锁和条件变量来实现读写锁。用法同互斥锁，还是承成对出现

  互斥锁：保护临界资源；然后逻判断指定的条件是否满足，不满足等待，释放锁

- 读写锁解锁：通过rw_refcount正负判断，类型，通过rw_nwaitwriters判断pthread_cond_signal类型。



### 信号量 

| 信号量 （也称信号灯） | Semaphore |      |
| --------------------- | --------- | ---- |
| 条件变量              | Condition |      |
| 互斥量                | Mutex     |      |





### 重要代码

~~~c++

Sem_init(&shared.mutex, 0, 1);
Sem_init(&shared.nempty, 0, NBUFF); //多写
Sem_init(&shared.nstored, 0, 0);///read




type RWMutex struct {
	w           Mutex  // held if there are pending writers //用于控制多个写锁，获得写锁首先要获取该锁，如果有一个写锁在进行，那么再到来的写锁将会阻塞于此
	writerSem   uint32 // semaphore for writers to wait for completing readers //写阻塞等待的信号量，最后一个读者释放锁时会释放信号量
	readerSem   uint32 // semaphore for readers to wait for completing writers //读阻塞的协程等待的信号量，持有写锁的协程释放锁后会释放readerCount个信号量
	readerCount int32  // number of pending readers //记录读者个数,获取读锁时简单+1,获取写锁时将其置为负值,用于标志已有协程持有了写锁
	readerWait  int32  // number of departing readers //获取写锁时，如果有读者，则将读者数记录于此，读者解锁时据此值来决定是否释放信号量，只有最后一个读者才需要释放信号量。
}

typedef struct {
  pthread_mutex_t	rw_mutex;		/* basic lock on this struct */
  pthread_cond_t	rw_condreaders;	/* for reader threads waiting */
  pthread_cond_t	rw_condwriters;	/* for writer threads waiting */
  int				rw_magic;		/* for error checking */
  int				rw_nwaitreaders;/* the number waiting */
  int				rw_nwaitwriters;/* the number waiting */
  int				rw_refcount;
	/* 4-1 if writer has the lock, else # readers holding the lock */
} pthread_rwlock_t;

//阻塞读锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rw)
{
	int		result;

	if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return(result);

	/* 4give preference to waiting writers */
	while (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0) {
		rw->rw_nwaitreaders++;
		result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
		rw->rw_nwaitreaders--;
		if (result != 0)
			break;
	}
	if (result == 0)
		rw->rw_refcount++;		/* another reader has a read lock */

	pthread_mutex_unlock(&rw->rw_mutex);
	return (result);
}
~~~

