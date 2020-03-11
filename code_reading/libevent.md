---
title: "协程库"
date: 2019-11-17
description: "高性能可扩展服务"
draft: false
categories: ["threads t"]

---

# 走神一会

你生而有翼，为何竟愿一生匍匐前进，形如虫蚁？

**「学而不思则罔、思而不学则殆」**的意思是：

想顺利的学会**「内思」**要与**「关系」**思考方式结合起来练。

否则，直接学**「内思」**，初学者会陷入练习的困境，这就是**罔**。

而只依靠**「关系」**思考方式，又会带来很大的危害，这就是**殆**。
作者：心智玩家的简书链接：https://www.jianshu.com/p/2940cf732b94来源

**「内思」**，用元神意识直接「看」意识影像，是需要经过一段时间的练习以后，才能达到的状态。没有经过练习，不容易做到。



| 协程库   | 版本 | 特性 |
| -------- | ---- | ---- |
| Libevent | 1.4  |      |
| Libevent | 2.1  |      |

# FQA

- 基本应用构建HTTP， TCP， PRC服务
- 多线程



# 学习记录

 ## 一、搜索文档

https://libevent.org/



https://file.ourfor.top/study/books-pdf/libevent参考手册(中文版).pdf

[https://github.com/KelvinYin/libevent-src-analysis/blob/master/libevent%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90.md](https://github.com/KelvinYin/libevent-src-analysis/blob/master/libevent源码分析.md)

http://www.ilovecpp.com/2018/04/14/libevent-preface/



https://aceld.gitbooks.io/libevent/content/8_evbuffer.html

http://www.ilovecpp.com/2018/04/20/lievent-trick/



http://www.wangafu.net/~nickm/libevent-book/



Reactor 模式是编写高性能网络服务器的必备技术之一，它具有如下的优点：

1）响应快，不必为单个同步时间所阻塞，虽然 Reactor 本身依然是同步的；

2）编程相对简单，可以最大程度的避免复杂的多线程及同步问题，并且避免了多线程/
进程的切换开销；

3）可扩展性，可以方便的通过增加 Reactor 实例个数来充分利用 CPU 资源；

4）可复用性， reactor 框架本身与具体事件处理逻辑无关，具有很高的复用性；  



###  libevent组件

- evutil：用于抽象不同平台网络实现差异的通用功能
- event和evelibeventnt_base：libevent的核心，为各种平台特定的、基于事件的非阻塞IO后端提供抽象API，让程序可以知道套接字何时已经准备好，可以读或者写，并且处理基本的超时功能，检测OS信号
- bufferevent：为libevent基于事件的核心提供使用更方便的封装。除了通知程序套接字已经准备好读写之外，还让程序可以请求缓冲的读写操作，可以知道何时IO已经真正发生
- evbuffer：在bufferevent层之下实现了缓冲功能，并且提供了方便有效的访问函数
- evhttp：一个简单的HTTP客户端/服务端实现
- evdns：一个简单的DNS客户端/服务端实现
- evrps：一个简单的RPC实现

https://aceld.gitbooks.io/libevent/content/chapter1.html

libevent包括事件管理、缓存管理、DNS、HTTP、缓存事件几大部分。

事件管理包括各种IO（socket）、定时器、信号等事件；

缓存管理是指evbuffer功能；

DNS是libevent提供的一个异步DNS查询功能；

HTTP是libevent的一个轻量级http实现，包括服务器和客户端。libevent也支持ssl

### 重点



- libevent支持多线程编程，每个事件需要关联到自己的event_base。

  

  http://www.cppblog.com/converse/archive/2015/05/11/71809.html

  https://stackoverflow.com/questions/21677154/libevent-multithreading-to-handle-http-keep-alive-connections?rq=1

  https://roncemer.com/software-development/multi-threaded-libevent-server-example/

  https://stackoverflow.com/questions/9153528/libevent-multithread-support/9305262#9305262

  https://gist.github.com/fxsjy/0170293e75eb53bbf007

  



# 二、动手实验

2.1 Libevent编译

```
wget https://github.com/libevent/libevent/archive/release-2.1.11-stable.tar.gz

cd libevent-release-2.1.11-stable
./autogen.sh 
./configure
/usr/local/include

	
补充：Linux下使用automake、autoconf生成configure文件
```



http://senlinzhan.github.io/2017/08/20/libevent-buffer/







# 项目应用

https://github.com/chenshuo/muduo

http://blog.codeg.cn/post/blog/2017-03-14-the-throughput-benchmark-test-of-evpp-vs-muduo/



https://gitee.com/zieckey/evpp/blob/master/docs/quick_start.md





https://github.com/Qihoo360/evpp



### 同类产品

## PhxRPC

[https://hellogithub.com/periodical/category/C%2B%2B%20%E9%A1%B9%E7%9B%AE/](https://hellogithub.com/periodical/category/C%2B%2B 项目/)

https://github.com/anhkgg/SuperWeChatPC/tree/master/sdk

## 参考

https://github.com/hungminhtran/daemon-demo/blob/master/libevent-http-demo.cpp

https://blog.csdn.net/lishenglong666/article/details/32111829