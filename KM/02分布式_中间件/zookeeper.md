##  陈咬金三板斧

### 一、这个技术出现的背景、初衷和要达到什么样的目标或是要解决什么样的问题

### 二、这个技术的优势和劣势分别是什么



微服务相关的项目都纷纷抛弃ZK转投etcd，可见其确实有可取之处，也可以看出一个项目的易用的重要性有时候甚至高于稳定性和功能

```shell
1  本身不是为高可用性设计， tps有限 cap中 cp 
```



### 三、这个技术适用的场景。任何技术都有其适用的场景，离开了这个场景



　**Zookeeper** 是一个基于 [Google Chubby](https://static.googleusercontent.com/media/research.google.com/zh-CN//archive/chubby-osdi06.pdf) 论文实现的一款解决分布式数据一致性问题的开源实现，方便了依赖 Zookeeper 的应用实现 

`数据发布 / 订阅`、`负载均衡`、`服务注册与发现`、`分布式协调`、`事件通知`、`集群管理`、`Leader 选举`、 `分布式锁和队列` 等功能





### 四、技术的组成部分和关键点。

ZAB 协议是为分布式协调服务 Zookeeper 专门设计的一种支持崩溃恢复的原子广播协议



### 五、技术的底层原理和关键实现

### 六、已有的实现和它之间的对比







https://mp.weixin.qq.com/s?__biz=MzI4MTY5NTk4Ng==&mid=2247489041&idx=1&sn=b58745994c0c98662e2330c966b5036f&source=41#wechat_redirect

https://juejin.im/post/5b924b0de51d450e9a2de615