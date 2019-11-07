# 衡量指标

分布式系统涵盖的面非常广，具体来说涵盖如下几方面：

- **服务调度**，涉及服务发现、配置管理、弹性伸缩、故障恢复等。
- **资源调度**，涉及对底层资源的调度使用，如计算资源、网络资源和存储资源等。
- **流量调度**，涉及路由、负载均衡、流控、熔断等。
- **数据调度**，涉及数据复本、数据一致性、分布式事务、分库、分表等。
- **容错处理**，涉及隔离、幂等、重试、业务补偿、异步、降级等。
- **自动化运维**，涉及持续集成、持续部署、全栈监控、调用链跟踪等。





### 服务调度衡量指标

#### 高可用:

 ![单点故障问题](https://static001.infoq.cn/resource/image/b5/2f/b5da20611e2d62ead9f1e54cfff7cb2f.png) 

可扩展

![image.png](https://i.loli.net/2019/11/05/j3Jleq58YwO1ZBR.png)

稳定性



# 业务场景

Q1 假如无法出现单点故障了，该怎么办？

> 例如 接受主播推流的srs，redis，还有proxy，还有普通的无法



回答：



- 有状态的无法，需要HA模式，或者多副本 2中集群模式
- 无状态，通过tb/ts方式，消息调度是一个集群，消息分发也是一个集群。

Redis集群方案应该怎么做？

 **1.Redis官方集群方案 Redis Cluster** 

 **2.Redis Sharding集群** 











# 产品

##  一. Kubernetes

### Kubernetes Autoscalin

## 二、服务网格Istio 



# 塔山之石

[1] [左耳朵耗子推荐：分布式系统架构经典资料](https://www.infoq.cn/article/2018/05/distributed-system-architecture) 【book 正在看，进展10%】

[2] [Istio Handbook——Istio 服务网格进阶实战]( https://www.servicemesher.com/istio-handbook/ )【book 正在看，进展0%】

[3] [云原生服务网格Istio：原理、实践、架构与源码解析](https://github.com/cloudnativebooks/cloud-native-istio) 【book 求电子书，感激不尽】

[4] [istio-introduction](ps://zhaohuabing.com/istio-practice/content/istio-introduction/) 【book 正在看，进展0%】

[5]  https://www.zhihu.com/question/21419897 [blog 正在看 进展0%]

[6] [Redis开发运维实践指南](https://www.w3cschool.cn/redis_all_about/) 【book 正在看，进展0%】

[7]  [Redis 设计与实现](http://redisbook.com/index.html) 

[8] [Redis内部数据结构详解]( http://zhangtielei.com/posts/server.html )   http://zhangtielei.com/posts/blog-redis-skiplist.html 

[9] [理解字节序](http://www.ruanyifeng.com/blog/2016/11/byte-order.html) [ok]

