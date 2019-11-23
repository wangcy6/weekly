---

title: "FQA_Service_Mesh"
date: 2019-11-13
description: "Service Mesh"
draft: false
tags: ["book","reading"]
categories: ["FQA"]
---


# book

-  **未来架构：从服务化到云原生** 
- 分布式缓存，从原理到实践
- 分布式系统：从概念到设计 第五版
- 深入理解Linux内核中文第三版  第五章 内核同步
- [distributed-systems-theory-for-the-distributed-systems-engineer](https://www.the-paper-trail.org/post/2014-08-09-distributed-systems-theory-for-the-distributed-systems-engineer/)

# 业务场景



## 衡量指标

分布式系统涵盖的面非常广，具体来说涵盖如下几方面：

- **服务调度**，涉及服务发现、配置管理、弹性伸缩、故障恢复等。
- **资源调度**，涉及对底层资源的调度使用，如计算资源、网络资源和存储资源等。
- **流量调度**，涉及路由、负载均衡、流控、熔断等。
- **数据调度**，涉及数据复本、数据一致性、分布式事务、分库、分表等。
- **容错处理**，涉及隔离、幂等、重试、业务补偿、异步、降级等。
- **自动化运维**，涉及持续集成、持续部署、全栈监控、调用链跟踪等。



#### 高可用:

 ![单点故障问题](https://static001.infoq.cn/resource/image/b5/2f/b5da20611e2d62ead9f1e54cfff7cb2f.png) 

#### 可扩展

![image.png](https://i.loli.net/2019/11/05/j3Jleq58YwO1ZBR.png)

#### 稳定性



## 高可用问题



Q1 假如无法出现单点故障了，该怎么办？

> 例如 接受主播推流的srs，redis，还有proxy，还有普通的无法
>
> 



回答：



- 有状态的无法，需要HA模式，或者多副本 2中集群模式
- 无状态，通过tb/ts方式，消息调度是一个集群，消息分发也是一个集群。

Redis集群方案应该怎么做？

 **1.Redis官方集群方案 Redis Cluster** 

 **2.Redis Sharding集群** 





## 主从 数据不一致性问题

>重点，超级重点

### 不切换 2pc

大王提问：

- 2阶段提交的缺点是什么? 

  > 小王回答：阻塞 然后xxxxx 

- 3pc直接有什么区别？

  > 小王回答：不阻塞了被，然后xxxxx 

大王批注：

> 你这是记忆，一看没做过项目，大家都直达，百度一下全都有，我看看

> 它 回滚失败怎办？
>
> 回去等消息吧



老王：那2pc优点是什么，大家都批评他，其他在2pc是怎么改进的？



| 协议 | 优点                                                         | 缺点                                                         | 代码库          |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------- |
| 2PC  | 强一致性，只要节点或者网络最终恢复正常，协议就能保证顺利结束 | 两阶段提交协议的容错能力较差，比如在节点宕机或者超时的情况下，无法确定流程的状态，只能不断重试 |                 |
| 3PC  | 在最后一阶段单点不阻塞                                       | 网络分区可能造成不一致                                       |                 |
| T cc | 锁冻结的资金,粒度降低了                                      |                                                              | tcc-transaction |



小王写了这个几句话

区别是:在网络出现分区情况下，默认超时处理方式不一样。



> two -phase commit  投票yes之后（query Commit），在一方故障的情况的下,需要通过读取日志记录事物的状态来恢复 判断
>
>  不能通过本地事务来推断整个事务状态判断，需要等待或者查询，来保证数据的一致性。

> three -phase commit 投票yes之后（pre Commit），如果出现网络原因，因为做了一次canCommit的统计，默认超时，转为do_commit ,
>
> 但是协调者也默认超时abort操作。这个时候可能数据的不一致。

![](https://user-images.githubusercontent.com/5937331/69323825-5c2dab00-0c82-11ea-89b8-06c019db8696.png)

> 来源网络

三阶段提交协议的不足

相对于2PC，3PC避免了协调者宕机之后可能出现的参与者们阻塞的情况。但仍然有较小的概率会导致不一致。





我绘制的

![2pc](https://i.loli.net/2019/11/23/3DYgsJoZLFzMiSR.png)



别人绘制的 

![image.png](https://i.loli.net/2019/11/23/4T1GpVglyhqjteY.png)

～～～～～～～～～～～～～～～～～我是分隔符 我来补充基本 ，不代表一定正确～～～～～～～～～～～





- 拜托，面试请不要再问我TCC分布式事务的实现原理！

​        https://juejin.im/post/5bf201f7f265da610f63528a 

​         https://yemablog.com/posts/tcc-1 





 https://roxanageambasu.github.io/ds-class//assets/lectures/lecture17.pdf 

从银行转账失败到分布式事务：总结与思考

 https://www.cnblogs.com/xybaby/p/7465816.html 

[分布式事务——2PC、3PC 和 TCC](http://huzb.me/2019/06/30/%E5%88%86%E5%B8%83%E5%BC%8F%E4%BA%8B%E5%8A%A1%E2%80%94%E2%80%942PC%E3%80%813PC%E5%92%8CTCC/)



#### 一致性问题

- 当协调者向所有参与者发送commit请求之后，发生了局部网络异常或协调者在尚未发完commit请求之前自身发生了崩溃，导致最终只有部分参与者接收到了commit请求。

  于是这部分参与者执行事务提交，而没收到commit请求的参与者则无法进行事务提交，于是整个分布式系统出现了数据不一致性现象。





```
Coordinator                                         Participant
                              QUERY TO COMMIT
                -------------------------------->
                              VOTE YES/NO           prepare*/abort*
                <-------------------------------
commit*/abort*                COMMIT/ROLLBACK
                -------------------------------->
                              ACKNOWLEDGMENT        commit*/abort*
                <--------------------------------  
end

https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/lecture8.html



牧师：”你愿意娶这个女人吗?爱她、忠诚于她，无论她贫困、患病或者残疾，直至死亡。Doyou(你愿意吗)?”

新郎：”Ido(我愿意)!”

牧师：”你愿意嫁给这个男人吗?爱他、忠诚于他，无论他贫困、患病或者残疾，直至死亡。Doyou(你愿意吗)?”

新娘：”Ido(我愿意)!”

牧师：现在请你们面向对方，握住对方的双手，作为妻子和丈夫向对方宣告誓言。

新郎：我——某某某，全心全意娶你做我的妻子，无论是顺境或逆境，富裕或贫穷，健康或疾病，快乐或忧愁，我都将毫无保留地爱你，我将努力去理解你，完完全全信任你。我们将成为一个整体，互为彼此的一部分，我们将一起面对人生的一切，去分享我们的梦想，作为平等的忠实伴侣，度过今后的一生。

新娘：我全心全意嫁给你作为你的妻子，无论是顺境或逆境，富裕或贫穷，健康或疾病，快乐或忧愁，我都将毫无保留的爱你，我将努力去理解你，完完全全信任你，我们将成为一个整体，互为彼此的一部分，我们将一起面对人生的一切，去分享我们的梦想，作为平等的忠实伴侣，度过今后的一生。
```

An * next to the record type means that the record is forced to stable storage.[[4\]](https://en.wikipedia.org/wiki/Two-phase_commit_protocol#cite_note-mohan1986-4)

![image.png](https://i.loli.net/2019/11/20/Lhza6UytbmeZ7pQ.png)



![image.png](https://i.loli.net/2019/11/20/3YHP2fOr815jCvZ.png)

#### ![阻塞的](https://i.loli.net/2019/11/13/5rVZHuK9QLcikEb.png) [3PC](https://app.yinxiang.com/shard/s39/nl/8226829/59f28292-cd0c-4c99-b43a-4405c133154c)  

```c++
> 一个节点故障，写入操作全部失败，整个系统崩溃？
https://en.wikipedia.org/wiki/Three-phase_commit_protocol
A two-phase commit protocol cannot dependably recover from a failure of both the coordinator and a cohort member during the Commit phase 【这里说是第二阶段】

If only the coordinator had failed, and no cohort members had received a commit message, it could safely be inferred that no commit had happened
    
(send 发送失败，不会提交业务的，原子操作，提交成功 然后返回结果) 原子操作类别pthread_cond_wait（1 wait 2unlock）
    
    Even if a new coordinator is selected, it cannot confidently proceed with the operation until it has received an agreement from all cohort members, and hence must block until all cohort members respond.
   
        The three-phase commit protocol eliminates this problem by introducing the Prepared to commit state (多了一个状态)
        
        
        If the coordinator fails before sending preCommit messages, the cohort will unanimously agree that the operation was aborted（没有准备，可以放弃）
        
        
        The coordinator will not send out a doCommit message until all cohort members have ACKed that they are Prepared to commit.（这里不发送）

   https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/lecture8.html     
 Recovery in 3PC

    
    
    
 脑洞


 如果有至少一个返回commit了，那么挂掉的节点只可能是prepare-commit和commit状态，这样整个系统状态也是可以提交的 


```

 ![img](https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/3pc-part.jpg) 

 ![img](https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/3pc-coord.jpg) 

 ![img](https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/2pc-part.jpg) 

 ![img](https://cseweb.ucsd.edu/classes/sp16/cse291-e/applications/ln/2pc-coord.jpg) 





～～～～～～～～～～～～～～～～～我是分隔符 我来补充基本 ，不代表一定正确 end～～～～～～～～～～～



### 全部一致  PacificA

![提交不变量](https://i.loli.net/2019/11/13/TYcnjfMLIN2hk97.png)

![image.png](https://i.loli.net/2019/11/13/ZJtYgPRMeo6r3pf.png)



### 过半一致 raft

![不断的重试，业务不阻塞](https://i.loli.net/2019/11/13/2TSnYU9ur7gf5Xm.png)



![image-20191121140300358](../../images/image-20191121140300358.png)

![image.png](https://i.loli.net/2019/11/21/8bci2MpPSJUtNvn.png)

### 弱一致（gossip）





# 数据库产品

![image.png](https://i.loli.net/2019/11/14/KTc9tlHFyaWioxI.png)

## rocksDB

 









# 服务产品

##  一. Kubernetes

### Kubernetes Autoscalin

## 二、服务网格Istio 







> A service mesh is a dedicated infrastructure layer for handling service-to-service communication. 
>
> It’s responsible for the reliable delivery of requests through the complex topology of services that comprise a modern, cloud native application. 
>
> In practice, the service mesh is typically implemented as an array of lightweight network proxies that are deployed alongside application code, without the application needing to be aware.
>
> 服务网格是一个基础设施层，用于处理服务间通信。
>
> 现代云原生应用有着复杂的服务拓扑结构，服务网格负责在这些拓扑结构中实现请求的可靠传递。
>
> 在实践中，服务网格通常被实现为一组轻量级网络代理，它们与应用程序部署在一起，对应用程序是透明的。 
>
> A *service mesh* is a configurable, low‑latency infrastructure layer designed to handle a high volume of network‑based interprocess communication among application infrastructure services using application programming interfaces (APIs).  



# 瞎扯

![image.png](https://i.loli.net/2019/11/21/5nTuUXIHow6xj2G.png)

# 塔山之石

[1] [左耳朵耗子推荐：分布式系统架构经典资料](https://www.infoq.cn/article/2018/05/distributed-system-architecture) 【book 正在看，进展10%】

[2] [Istio Handbook——Istio 服务网格进阶实战]( https://www.servicemesher.com/istio-handbook/ )【book 正在看，进展0%】

[3] [云原生服务网格Istio：原理、实践、架构与源码解析](https://github.com/cloudnativebooks/cloud-native-istio) 【book 求电子书，感激不尽】

   迁移到云原生应用架构  https://jimmysong.io/migrating-to-cloud-native-application-architectures/ 



[4] [istio-introduction](ps://zhaohuabing.com/istio-practice/content/istio-introduction/) 【book 正在看，进展0%】

[5]  https://www.zhihu.com/question/21419897 [blog 正在看 进展0%]

[6] [Redis开发运维实践指南](https://www.w3cschool.cn/redis_all_about/) 【book 正在看，进展0%】

[7]  [Redis 设计与实现](http://redisbook.com/index.html) 

[8] [Redis内部数据结构详解]( http://zhangtielei.com/posts/server.html )   http://zhangtielei.com/posts/blog-redis-skiplist.html 

[9] [理解字节序](http://www.ruanyifeng.com/blog/2016/11/byte-order.html) [ok]

[10] 服务网格是什么？  https://www.nginx.com/blog/what-is-a-service-mesh/  

[11] MySQL高可用在网易的最佳应用与实践



