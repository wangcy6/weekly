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



**历史渊源**



首先介绍一下这个库的历史渊源，从代码贡献者来看，ST不是个人作品，而是有着雄厚的商业支持和应用背景，比如服务器领域，在[这里](http://state-threads.sourceforge.net/news.html)你可以看到ST曾作为Apache的多核应用模块发布。

其诞生最初是由网景（Netscape）公司的MSPR（Netscape Portable Runtime library）项目中剥离出来，后由SGI（Silicon Graphic Inc）还有Yahoo!公司（前者是主力）开发维护的独立线程库。

版本方面，作为[SourceForge](http://sourceforge.net/projects/state-threads/files/)上开源项目， 

由2001年发布v1.0以来一直到2009年v1.9稳定版后未再变动。

在平台移植方面，从Makefile的配置选项中可知ST支持多种Unix-like平台，还有专门针对Win32的源码改写。

源码例子中，提供了web server、proxy以及dns三种编程实例供参考。

**可以说代码质量应该是相当的稳定和可靠的。**

# 卡片

| 协程库                | 语言                                                         | 开发者                                               |
| --------------------- | ------------------------------------------------------------ | ---------------------------------------------------- |
| state threads library | 3000行[C代码](https://github.com/wangcy6/reading_code_note/tree/master/liunx/st) | [历史渊源](https://coolshell.cn/articles/12012.html) |
|                       |                                                              |                                                      |

# 学习记录

 ## 一、搜索文档

#### 阅读文档1 ，累计盘茄次数    耗时 120分钟



理解 **ST本质上仍然是基于[EDSM模型](https://coolshell.cn/articles/12012.html)，但旨在取代传统的异步回调方式** ,**为[互联网应用程](https://github.com/zfengzhen/Blog/blob/master/article/%E4%B8%BA%E4%BA%92%E8%81%94%E7%BD%91%E5%BA%94%E7%94%A8%E7%A8%8B%E5%BA%8F%E8%80%8C%E7%94%9F%E7%9A%84State%20Threads%5B%E5%B8%B8%E8%A7%81%E5%90%8E%E5%8F%B0%E6%9E%B6%E6%9E%84%E6%B5%85%E6%9E%90%5D.md)序而生[的State Threads](https://www.cnblogs.com/NerdWill/p/6166220.html)** 

 

涉及内容

**State Threads Library Documentation**

- [**Introductory paper**](http://state-threads.sourceforge.net/docs/st.html)
- [**Complete reference**](http://state-threads.sourceforge.net/docs/reference.html)
- [**Programming notes**](http://state-threads.sourceforge.net/docs/notes.html)
- [**Frequently Asked Questions and answers (FAQ)**](http://state-threads.sourceforge.net/docs/faq.html)







## 二、动手



暂无

# 项目应用

暂无



