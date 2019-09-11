### 知识地图



### 感觉

1. 我发送一个大包，系统拆分成 ，例如 A ,B C, D , 四个小包，怎么保证对方按照 A B CD 正确组装起来 完成数据正确传输，我不停发送n个大包呢？

2.   假如四次握手，最后一个阶段 断网，主动关闭一个无法发送ack请求，被动关闭一方无限重试 发送FIN，

   是不是一直处于last_ack 状态？这个端口就无法使用了，因为time_wait 会自动消失. close_wait不会

   那last_ack呢？

   ```
   https://maimai.cn/web/gossip_detail?encode_id=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlZ2lkIjoiOWJlYmJjMTBkNDY0MTFlOTk2MDEyNDZlOTZiNDgwODgiLCJpZCI6MjM2MjgwMDV9.-w1LLJogTeBaU16ex65j0AVXY9xCkq2QkfY9MCqp6o0
   
   https://www.zhihu.com/question/27564314/answer/162476313
   https://networkengineering.stackexchange.com/questions/38805/why-is-the-last-ack-needed-in-tcp-four-way-termination
   ```

   

### 原理

### 1. TCP

- 状态机

![](http://www.4e00.com/blog/img/linux/tcp/tcpip-state-transition-diagram.png)

![](https://www.zhuxiaodong.net/static/images/tcp_close.png)

什么建链接要3次握手，断链接需要4次挥手？

[TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)

[TCP 的那些事儿（下）](https://coolshell.cn/articles/11609.html)

```c++
http://www.tcpipguide.com/free/t_TCPConnectionTermination-4.htm

http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html
https://github.com/jawil/blog/issues/14


```



- ### Purposes for the TIME-WAIT state

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



![](http://www.4e00.com/blog/img/linux/tcp/tcp-close-duplicate-segment.svg)

```
TIME-WAIT Assassination Hazards in TCP【官方文档】
https://tools.ietf.org/html/rfc1337



https://networkengineering.stackexchange.com/questions/38805/why-is-the-last-ack-needed-in-tcp-four-way-termination

https://www.zhuxiaodong.net/2018/tcp-time-wait-instruction/

https://www.zhihu.com/question/27564314/answer/162476313

https://vincent.bernat.ch/en/blog/2014-tcp-time-wait-state-linux#purpose
```

- TCP Retransmission

https://www.extrahop.com/company/blog/2016/retransmission-timeouts-rtos-application-performance-degradation/



- RST 终止连接示例

```c
struct linger {    
 int l_onoff;  /* 0=off, nonzero=on */  
 int l_linger; /* linger time, POSIX specifies units as seconds */};

http://www.4e00.com/blog/linux/2019/03/27/tcp-option-so-linger.html
```

### 工具

- 查看服务TCP 状态

   netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'

-  ss - another utility to investigate sockets

  ss -tan |head -10



### 案例

### 参考



https://tools.ietf.org/html/rfc1337

TRANSMISSION CONTROL PROTOCOL



