# 知识地图



思维导图 后面补充



# 思考与行动

1. 我发送一个大包，系统拆分成 ，例如 A ,B C, D , 四个小包，怎么保证对方按照 A B CD 正确组装起来 完成数据正确传输，我不停发送n个大包呢？

2.   假如四次握手，最后一个阶段 断网，主动关闭一个无法发送ack请求，被动关闭一方无限重试 发送FIN，

   是不是一直处于last_ack 状态？这个端口就无法使用了，因为time_wait 会自动消失. close_wait不会

   那last_ack呢？

   
   
   3 .下面场景可能存在吗，有什么问题。
   
   
   

   
   ![image.png](https://upload-images.jianshu.io/upload_images/1837968-5acfb851a759aa67.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

# TCP原理

## 任务1 手绘TCP协议的状态机

> 如果感觉很简单，请2分钟完成，并且不看答案 保证100%正确，

> 如果感觉模糊不清地费，说明知识有缺陷，必须深入研究明白。
>
> 如果感觉都没有问题，请回答下面几个问题，3句话描述

![](http://www.4e00.com/blog/img/linux/tcp/tcpip-state-transition-diagram.png)

![](https://www.zhuxiaodong.net/static/images/tcp_close.png)

![](https://coolshell.cn/wp-content/uploads/2014/05/tcpfsm.png)

![](https://coolshell.cn/wp-content/uploads/2014/05/tcpclosesimul.png)



#### 问题：tcp 协议格式

- **Sequence Number**是包的序号，**用来解决网络包乱序（reordering）问题。**
- **Acknowledgement Number**就是ACK——用于确认收到，**用来解决不丢包的问题**。
- **Window又叫Advertised-Window**，也就是著名的滑动窗口（Sliding Window），**用于解决流控的**。
- **TCP Flag** ，也就是包的类型，**主要是用于操控TCP的状态机的**。



#### 问题   对于4次挥手 -如何断开连接的



什么建链接要3次握手，断链接需要4次挥手？

[TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)

[TCP 的那些事儿（下）](https://coolshell.cn/articles/11609.html)

```c++
http://www.tcpipguide.com/free/t_TCPConnectionTermination-4.htm

http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html
https://github.com/jawil/blog/issues/14


```

#### 问题：对于4次挥手 -Purposes for the TIME-WAIT state

2*MSL（[RFC793](http://tools.ietf.org/html/rfc793)定义了MSL为2分钟，Linux设置成了30s）为什么要这有TIME_WAIT？

1. 确保被动关闭一方(close_wait) 优先关闭关闭，也就是说在规定时间这个ack一定要达到（除非自己挂了 网络不可达其他错误），if出现网络拥塞情况造成不可达， then 对方超时重传发送fin，主动关闭重新计时2SML  MSL (the packet lifetime)
    不然被动处于last_ack 状态，无法建立新连接。不可高。 if crash  rst

   > The other purpose is to ensure **the remote end has closed the connection**
   >
   > So, if that last packet is dropped, the server will retransmit it (it is, after all, an unacknowledged segment) and will expect to see a suitable ACK segment in reply. 
   >
   > If the client went straight to CLOSED, the only possible response to that retransmit would be a RST, which would indicate to the server that data had been lost, when in fact it had not been.
   
   
   
   > The end that sends the first FIN goes into the TIME_WAIT state, because that is the end that sends the final ACK. If the other end's FIN is lost, or if the final ACK is lost, having the end that sends the first FIN maintain state about the connection guarantees that it has enough information to retransmit the final ACK.
   
   > 来源：**2.7  Please explain the TIME_WAIT state.**http://web.deu.edu.tr/doc/soket/
   
   



​           ![](https://www.zhuxiaodong.net/static/images/why-time-wait-2.png)



  



1. TCP 全双工的，虽然主动关闭一方发送CLOSE 不会传输数据，对方依然可以传输数据，保证延迟数据 。如果不等待对方一段时间，主动关闭一方建立新连后接受错误业务数据。

   > The most known one is to **prevent delayed segments** from one connection being accepted by a later connection relying on the same quadruplet (source address, source port, destination address, destination port)

![](https://www.zhuxiaodong.net/static/images/why-time-wait-1.png)



![](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/TIME_WAIT-why-thumb-500x711-277.png)

![](http://www.4e00.com/blog/img/linux/tcp/tcp-close-duplicate-segment.svg)

```
TIME-WAIT Assassination Hazards in TCP【官方文档】
https://tools.ietf.org/html/rfc1337



https://networkengineering.stackexchange.com/questions/38805/why-is-the-last-ack-needed-in-tcp-four-way-termination

https://www.zhuxiaodong.net/2018/tcp-time-wait-instruction/

https://www.zhihu.com/question/27564314/answer/162476313

https://vincent.bernat.ch/en/blog/2014-tcp-time-wait-state-linux#purpose

https://maimai.cn/web/gossip_detail?encode_id=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlZ2lkIjoiOWJlYmJjMTBkNDY0MTFlOTk2MDEyNDZlOTZiNDgwODgiLCJpZCI6MjM2MjgwMDV9.-w1LLJogTeBaU16ex65j0AVXY9xCkq2QkfY9MCqp6o0

https://www.zhihu.com/question/27564314/answer/162476313
https://networkengineering.stackexchange.com/questions/38805/why-is-the-last-ack-needed-in-tcp-four-way-termination
```



**使用tcp_tw_reuse和tcp_tw_recycle来解决TIME_WAIT的问题是非常非常危险的，因为这两个参数违反了TCP协议（RFC 1122）** 





#### 问题：TCP Retransmission



1 TCP要保证所有的数据包都可以到达，所以，必需要有重传机制。

2 **Acknowledgement Number**就是ACK——用于确认收到，**用来解决不丢包的问题**。

 在数据传输阶段，确认序号将发送方的序号加发送的数据大小作为回答

握手阶段，确认序号将发送方的序号加1作为回答

3 **ack的时候，不能跳着确认，只能确认最大的连续收到的包**



```
TCP 的那些事儿（上）

https://www.extrahop.com/company/blog/2016/retransmission-timeouts-rtos-application-performance-degradation/

https://www.javazhiyin.com/33012.html
```



- RST 终止连接示例

```c
struct linger {    
 int l_onoff;  /* 0=off, nonzero=on */  
 int l_linger; /* linger time, POSIX specifies units as seconds */};

http://www.4e00.com/blog/linux/2019/03/27/tcp-option-so-linger.html
```



### 小王 偷偷写这么几句话



time_wait 存在的意义2点：

一 , tcp 是可靠传输，在服务正常（不重启），网络正常的情况下（不断网），确保最有一个ack包，一定达到对方，保证对方端口正确释放。（哪有100%事情，一定，刮风下雨，地震火灾都可能）

采用方式是(flag=Fin)，

> 每次收到对方的flag=Fin，重新计时。在2MSL，足够保证当前发送的ACK正确到达或者在网络中消失
>
> 最极点情况 对方发送多次，3次×60=180秒。time_wait原来的30秒 延长到180秒

如果对方不系统配置不支持重传或者断网情况下 或者core，接受不到Fin怎么办？

> 这个情况，已经不可能解决事情，超出发送方的处理能力，自己就不处理，难道我系统就不运行了
>
> 这个情况在last_ack一方 ，Retransmission超时 ，rst异常方式结束。



二， 在条件1完成情况下，因为tcp全双工传输，拒绝端口马上重用，防止old连接延迟数据对new的连接造成混乱。

条件：发送方 发送一个ack包，然后到对方（5 秒呢）地方已经关闭，现在马上释放呢 有什么问题？（ITME_WAIT 设置60秒）

> 因为tcp传输方式IP +port方式，对于old连接，虽然不会主动发送数据，但是依然可以接受数据.



呵呵呵

time_wait 存在的意义

一、保证TCP协议的全双工连接能够可靠关闭
二、保证这次连接的重复数据段从网络中消失



### 问题 socket 基本函数用法知道 ? 

> socket /connect/accept/read/write/close?



参考 趣谈Linux操作系统 网卡收发报的原理 







## 案例分析

> 查看服务TCP 状态

netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'





```shell
netstat -atnp | grep -i ":500"
Proto Recv-Q Send-Q Local Address           Foreign Address         State  
    tcp        0      0 0.0.0.0:500             0.0.0.0:*               LISTEN      -
    tcp        0      0 192.168.1.10:500        192.168.1.13:26813      ESTABLISHED -
```



ss - another utility to investigate sockets

ss -tan |head -10

一个TCP连接需要四个元组来表示是同一个连接（src_ip, src_port, dst_ip, dst_port）准确说是五元组，

还有一个是协议。但因为这里只是说TCP协议，所以，这里我只说四元组。



# 生活场景

### 电影旁边



不上班行不行？”

“不上班你养我啊”

“我养你啊”

“你还是先照顾好自己吧，傻瓜。”





### 参考

- [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)
- TIME-WAIT Assassination Hazards in TCP

​        https://tools.ietf.org/html/rfc1337

- [TCP套接字端口复用SO_REUSEADDR](https://www.cnblogs.com/kex1n/p/7437290.html)

- [TIME_WAIT and its design implications for protocols and scalable client server systems](http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html)

