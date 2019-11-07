# 基本用法

## 负载均衡

### 1 负载均衡概念是什么

11 观看[HAProxy](http://www.haproxy.org/)相关视频

![image.png](https://i.loli.net/2019/11/07/BWiDyafS4YGJeU8.png)

10.  [Virtual IP address](https://en.wikipedia.org/wiki/Virtual_IP_address) ok

 A **virtual IP address** (**VIP** or **VIPA**) is an [IP address](https://en.wikipedia.org/wiki/IP_address) that doesn't correspond to an actual physical network interface. 



 VIP addresses are also used for connection redundancy by providing alternative fail-over options for one machine 

使用 keepalived 设置虚拟 IP 环境



9. [现代网络负载均衡与代理（下）](https://blog.envoyproxy.io/introduction-to-modern-network-load-balancing-and-proxying-a57f6ff80236) ok

8. 英文： https://blog.envoyproxy.io/introduction-to-modern-network-load-balancing-and-proxying-a57f6ff80236 

   翻译： https://www.infoq.cn/article/modern-network-load-balancing-and-proxying-1 

   The L4 load balancer is unaware of any application details of the bytes that it is shuffling. The bytes could be HTTP, Redis, MongoDB, or any other application protocol. 





7. 阅读Istio深度解析与项目实践 文章  https://zhaohuabing.com/istio-practice/ 

6.  **load balancer proxy不能成为单点故障**（single point of failure），因此一般会设计为高可用的主从结构 

5. 阅读 Nginx七层负载均衡 完毕，

   理解了一句话 

   - 了解存在负载的软件  Nginx 7， Haproxy  LVS 
   - 扩展到 [转发和代理]( https://www.youtube.com/watch?v=UPiHkCmprtE )

4. 阅读 知乎文章一篇 [四层负载均衡和七层负载均衡区别在哪里](https://zhuanlan.zhihu.com/p/34904010)？

   jump ：

   -  四层负载均衡工作在OSI模型的传输层，主要工作是转发，它在接收到客户端的流量以**后通过修改数据包的地址信息**将流量转发到应用服务器 
   -  七层负载均衡的主要工作就是代理 
   -  最初美团点评使用的是LVS+Nginx组成的负载均衡结构，LVS做四层负载均衡，Nginx做七层负载均衡 

3. 阅读 [基于 nginx 的七层负载均衡实现初步](https://klionsec.github.io/2017/07/27/nginx-lbd/) 了解nginx基本配置

2. 我阅读了[An Introduction to HAProxy and Load Balancing Concepts](https://www.digitalocean.com/community/tutorials/an-introduction-to-haproxy-and-load-balancing-concepts) 

   理解了一句话 

   - Layer 4 Load Balancing ip:port, Layer 7 Load Balancing url  

   -  HAProxy, which stands for High Availability Proxy, is a popular open source software TCP/HTTP Load Balancer and proxying solution which can be run on Linux, Solaris, and FreeBSD.  

   -   Floating IPs 

      



1. 我阅读了 维基百科 定义 **负载均衡** 的[解释](https://zh.wikipedia.org/wiki/%E8%B4%9F%E8%BD%BD%E5%9D%87%E8%A1%A1)      

   理解了一句话  

   - 负载均衡经常被用于实现[故障转移](https://zh.wikipedia.org/wiki/故障转移) --解决单点故障问题

   











### 2 负载均衡策略

>如果你上来说这个肯定是错误的，理解不正确，从架构上设计上来体会 回到#四层负载均衡和七层负载均衡

-  round-robin 

-  ip_hash  

-  least_conn    

  

#### http 协议（3次腾讯，滴滴，陌陌）

#### http协议格式

一个HTTP请求报文由请求行（request line）、请求头部（header）、空行和请求数据4个部分组成，下图给出了请求报文的一般格式。

![img](https://pic002.cnblogs.com/images/2012/426620/2012072810301161.png)

 https://my.oschina.net/manmao/blog/549123 

![image-20191105193926198](../../images/image-20191105193926198.png)

![image-20191105194051987](../../images/image-20191105194051987.png)

~~~
(1)请求方法  URI 协议/版本
  请求的第一行是“方法URL协议版本”：

GET/sample.jsp HTTP/1.1
 以上代码中“GET”代表请求方法，“/sample.jsp”表示URI，“HTTP/1.1代表协议和协议的版本。

  根据HTTP标准，HTTP请求可以使用多种请求方法。例如：HTTP1.1支持7种请求方法：GET、POST、HEAD、OPTIONS、 PUT、DELETE和TARCE。在Internet应用中，最常用的方法是GET和POST。

 URL完整地指定了要访问的网络资源，通常只要给出相对于服务器的根目录的相对目录即可，因此总是以“/”开头，最后，协议版本 声明了通信过程中使用HTTP的版本。

(2)请求头(Request Header)
请求头包含许多有关的客户端环境和请求正文的有用信息。例如，请求头可以声明浏览器所用的语言，请求正文的长度等。

Accept:image/gif.image/jpeg.*/*
Accept-Language:zh-cn
Connection:Keep-Alive
Host:localhost
User-Agent:Mozila/4.0(compatible:MSIE5.01:Windows NT5.0)
Accept-Encoding:gzip,deflate.


(3)请求正文
请求头和请求正文之间是一个空行，这个行非常重要，它表示请求头已经结束，接下来的是请求正文。请求正文中可以包含客户提 交的查询字符串信息：

username=jinqiao&password=1234
~~~

![image-20191105194352975](../../images/image-20191105194352975.png)

~~~asp
HTTP/1.0 200 OK 
Content-Type: text/plain
Content-Length: 137582
Expires: Thu, 05 Dec 1997 16:00:00 GMT
Last-Modified: Wed, 5 August 1996 15:55:28 GMT
Server: Apache 0.84

<html>
  <body>Hello World</body>
</html>

~~~

![image-20191105200334270](../../images/image-20191105200334270.png)

- Wireshark：抓取 HTTP 包
-  *tcpdump*  

#### HTTP请求方法介绍区别

 http://liufeize.com/2017/11/10/The-difference-between-the-GET-and-POST/ 

#### get和post区别



> 错误的回答

~~~shell
曾经有一个研读了HTTP协议的人去一家公司面试，面试官问他这个问题时，
他回答“GET是用于获取数据的，POST一般用于将数据发给服务器。其他GET和POST没什么区别”，
于是被刷了。
因为有些面试官心中也只有那一个“标准答案”。
谁说 HTTP GET 就不能通过 Body 来发送数据呢？

GET和POST还有一个重大区别，简单的说：

GET产生一个TCP数据包；POST产生两个TCP数据包。

 一个实体由实体报头域和实体正文组成，但并不是说实体报头域和实体正文要在一起发送，

可以只发送实体报头域 

长的说：

对于GET方式的请求，浏览器会把http header和data一并发送出去，服务器响应200（返回数据）；

而对于POST，浏览器先发送header，服务器响应100 continue，浏览器再发送data，服务器响应200 ok（返回数据）。

也就是说，GET只需要汽车跑一趟就把货送到了，而POST得跑两趟，第一趟，先去和服务器打个招呼“嗨，我等下要送一批货来，你们打开门迎接我”，然后再回头把货送过去。

关于『GET 发一个包，POST 发两个包』

对于GET方式的请求，浏览器会把http header和data一并发送出去，服务器响应200（返回数据）；
而对于POST，浏览器先发送header，服务器响应100 continue，浏览器再发送data，服务器响应200 ok（返回数据）。

测试结果如下：

Chrome 55.0.2883.95，two packets: YES
Safari 10.0.2, two packets: YES
Firefox 49.0, two packets: NO
~~~

> 正确回答



> curl -v -X GET  www.baidu.com -d "test" 

 



#### 如何防范 POST 重复提交

编程中，一个幂等操作的特点是其任意多次执行所产生的影响均与一次执行的影响相同 

假设有一个从账户取钱的远程 API（可以是 HTTP 的，也可以不是），我们暂时用类函数的方式记为：

bool withdraw(account_id, amount)

![https://img3.fanhaobai.com/2017/05/api-idempotence/033718EYW.png](https://img3.fanhaobai.com/2017/05/api-idempotence/033718EYW.png)

把分布式事务分解为具有幂等性的异步消息处理

> 利用 Web API 的形式实现前面所提到的取款功能。

1、用 POST /tickets 来实现 create_ticket；
2、用 PUT /accounts/account_id/ticket_id&amount=xxx 来实现 idempotent_withdraw；

值得注意的是严格来讲 amount 参数不应该作为 URI 的一部分，真正的 URI 应该是 /accounts/account_id/ticket_id，而 amount 应该放在请求的 body 中。这种模式可以应用于很多场合，比如：论坛网站中防止意外的重复发帖。

### 3. 案例

 观止云开源流媒体服务器SRS（Simple RTMP Server）

- master就是主服务器，负责转发流给其他服务器。
- slave：从服务器，主服务器转发流到这个服务器。
-  小型集群 

```scheme
                     +-------------+    +---------------+
                               +-->+ Slave(1935) +->--+  Player(3000) +
                               |   +-------------+    +---------------+
                               |   +-------------+    +---------------+
                               |-->+ Slave(1936) +->--+  Player(3000) +
         publish       forward |   +-------------+    +---------------+
+-----------+    +--------+    |     192.168.1.6                       
|  Encoder  +-->-+ Master +-->-|                                       
+-----------+    +--------+    |   +-------------+    +---------------+
 192.168.1.3    192.168.1.5    +-->+ Slave(1935) +->--+  Player(3000) +
                               |   +-------------+    +---------------+
                               |   +-------------+    +---------------+
                               +-->+ Slave(1936) +->--+  Player(3000) +
                                   +-------------+    +---------------+
                                     192.168.1.7     
```

[开源流媒体服务器SRS学习笔记(4) - Cluster集群方案](https://www.cnblogs.com/yjmyzz/p/srs_study_4_cluster.html)

 好问题：

> 如主播推流到源站节点A, 节点A宕机了,  推流到节点B. 此时有一个源站切换, 用户会感知到卡  
>
>  https://github.com/ossrs/srs/issues/938 

--------------------------------------------------华丽分隔符 基本知识补充-----------------------------------------------------------------

- SRS 边缘(edge) ()实现自动切换

   SRS的Edge提供访问时回源机制 

在全国32个省每个省都部署了10台服务器，一共就有320台边缘，假设每个省1台边缘服务器都有 2000用户观看，那么就有64万用户，每秒钟集群发送640Gbps数据；而回源链接只有320个， 实现了大规模分发 

 可配置`多个`源站，在故障时会切换到下一个源站【主挂了edge依然能获取，实现自动切换】 



```c
vhost __defaultVhost__ {
    # the mode of vhost, local or remote.
    #       local: vhost is origin vhost, which provides stream source.
    #       remote: vhost is edge vhost, which pull/push to origin.
    # default: local
    mode            remote;
    # for edge(remote mode), user must specifies the origin server
    # format as: <server_name|ip>[:port]
    # @remark user can specifies multiple origin for error backup, by space,
    # for example, 192.168.1.100:1935 192.168.1.101:1935 192.168.1.102:1935
    origin          127.0.0.1:1935 localhost:1935;
    # for edge, whether open the token traverse mode,
    # if token traverse on, all connections of edge will forward to origin to check(auth),
    # it's very important for the edge to do the token auth.
    # the better way is use http callback to do the token auth by the edge,
    # but if user prefer origin check(auth), the token_traverse if better solution.
    # default: off
    token_traverse  off;
}
```

--------------------------------------------------华丽分隔符 基本知识补充-----------------------------------------------------------------

 边缘服务器前置反向代理（比如：nginx），用于提供统一的播放地址，同时解决跨域问题，给客户端拉流播放 

 源站前置负载均衡（硬件或软件负载均衡都行），上图中用HA proxy来实现tcp的软负载均衡。 







# 参考

[1] 图解HTTP 第三章 第四章节（第一次看发现全部都是解释字段含义，产生没有什么学的感觉。第二次看http协议格式）c

[2]  https://zhaohuabing.com/istio-practice/ 

