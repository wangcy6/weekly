# FQA

- 如主播推流到源站节点A, 节点A宕机了,  推流到节点B. 此时有一个源站切换, 用户会感知到卡  

  https://github.com/ossrs/srs/issues/938 ?
  
  https://github.com/ossrs/srs/issues/464
  
  https://github.com/ossrs/srs/wiki/v3_CN_OriginCluster
  
  



# 基本用法

## 一. 负载均衡

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

   

2 负载均衡策略

>如果你上来说这个肯定是错误的，理解不正确，从架构上设计上来体会 回到#四层负载均衡和七层负载均衡

-  round-robin 

-  ip_hash  

-  least_conn    

  

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



图片有热备，静态资源。没有问题。正在推送的流呢?不可能有2个吧？













##  二.  Nginx平滑升级源码分析

### 2. 1 解决问题

如果需要升级Nginx或者更改编译配置，不需要kill掉Nginx的master进程，

这样会断开正在连接中的TCP请求，造成短时间内服务器不可用



### 2.2 平滑升级步骤



**一、平滑升级操作步骤**



1、备份原Nginx二进制文件；

2、编译新Nginx源码，安装路径需与旧版一致；

3、向主进程发送`USR2`信号，Nginx会启动一个新版本的master进程和工作进程，和旧版一起处理请求：

```powershell
prey:~ root# ps -ef|grep nginx
 127     1   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
 129   127   nginx: worker process
prey:~ root# kill -USR2 127
prey:~ root# ps -ef|grep nginx
 127     1   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
 129   127   nginx: worker process  
5180   127   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
5182  5180   nginx: worker process
```

**这个时候新老Nginx都会接收请求，看那一个进程能抢到锁，抢到锁的worker进程可以accept新请求**



4、向原Nginx主进程发送`WINCH`信号，它会逐步关闭旗下的工作进程（主进程不退出），这时所有请求都会由新版Nginx处理：

```
prey:~ root# kill -WINCH 127
prey:~ root# ps -ef|grep nginx
 127     1   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
5180   127   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
5182  5180   nginx: worker process
```

5、如果这时需要回退，可向原Nginx主进程发送`HUP`信号，它会重新启动工作进程， **仍使用旧版配置文件** 。尔后可以将新版Nginx进程杀死（使用`QUIT`、`TERM`、或者`KILL`）：

6、如果不需要回滚，可以将原Nginx主进程杀死，至此完成热升级。

```
prey:~ root# kill 127
prey:~ root# ps -ef|grep nginx
5180     1   nginx: master process /usr/local/nginx-1.2.4/sbin/nginx
5182  5180   nginx: worker process
```

切换过程中，Nginx会将旧的`.pid`文件重命名为`.pid.oldbin`文件，并在旧进程退出后删除。



热升级过程:

可以先思考一下一些难点:

- 在操作系统层面是不允许两个进程监听同一个端口的,那么优雅升级时如何让新旧进程同时处理监听端口上的请求

- 如何让旧的worker process 不再接收请求,并且处理完当前请求后退出

  

### 3.3 部分代码

 ngx_process_cycle.c

   ngx_signal_handler  



```c
#define NGX_REOPEN_SIGNAL        USR1
#define NGX_CHANGEBIN_SIGNAL     USR2
#define NGX_SHUTDOWN_SIGNAL      QUIT
#define NGX_TERMINATE_SIGNAL     TERM
#define NGX_NOACCEPT_SIGNAL      WINCH
#define NGX_RECONFIGURE_SIGNAL   HUP

             
```









ngx_signal_handler -->ngx_change_binary -->ngx_master_process_cycle

#### ngx_signal_handler

case SIGCHLD:
            ngx_reap = 1;



if (signo == SIGCHLD) {
        ngx_process_get_status();



   

​    }





#### ngx_master_process_cycle  创建完成后，主要停留在这里接受信号

~~~c
150行代码
    
for ( ;; ) {
      
        sigsuspend(&set); //每次处理完一个信号，master进程会被挂起，直到有新的信号到来

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                       "wake up, sigio %i", sigio);
        /**
		 * 回收子进程,这里的回收是针对全局数组 ngx_processes, 
		 * 操作系统层面的进程回收已经在信号处理函数 ngx_signal_handler() 中完成, 
		 * 并对ngx_processes 的相应条目中进行了标记
		 */
        if (ngx_reap) {
            ngx_reap = 0;
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, cycle->log, 0, "reap children");

            live = ngx_reap_children(cycle);
        }
        /* 没有worker进程存活时，master进程才退出*/
        if (!live && (ngx_terminate || ngx_quit)) {
            ngx_master_process_exit(cycle);
        }

        if (ngx_terminate) {
            if (delay == 0) {
                delay = 50;
            }

            if (sigio) {
                sigio--;
                continue;
            }

            sigio = ccf->worker_processes + 2 /* cache processes */;

            if (delay > 1000) {
                ngx_signal_worker_processes(cycle, SIGKILL);
            } else {
                ngx_signal_worker_processes(cycle,
                                       ngx_signal_value(NGX_TERMINATE_SIGNAL));
            }

            continue;
        }

        if (ngx_quit) {
            ngx_signal_worker_processes(cycle,
                                        ngx_signal_value(NGX_SHUTDOWN_SIGNAL));

            ls = cycle->listening.elts;
            ////关闭所有socket套接字
            for (n = 0; n < cycle->listening.nelts; n++) {
                if (ngx_close_socket(ls[n].fd) == -1) {
                    ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                                  ngx_close_socket_n " %V failed",
                                  &ls[n].addr_text);
                }
            }
            cycle->listening.nelts = 0;

            continue;
        }
       //收到SIGHUP信号，
        if (ngx_reconfigure) {
            ngx_reconfigure = 0;
              //如果是平滑升级程序，则重启worker进程，不需要重新初始化配置
            if (ngx_new_binary) {
                   //启动ccf->worker_processes个worker子进程，并设置好每个子进程与
                //master父进程之间使用socketpair系统调用建立起来的socket句柄通信机制
                //启动方式为NGX_PROCESS_RESPAWN,该值影响ngx_process_t结构体的respawn
                ngx_start_worker_processes(cycle, ccf->worker_processes,
                                           NGX_PROCESS_RESPAWN);

                //执行缓存管理工作的循环方法
                ngx_start_cache_manager_processes(cycle, 0);
                ngx_noaccepting = 0;

                continue;
            }

            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reconfiguring");
          //不是平滑升级，重新读取配置
            cycle = ngx_init_cycle(cycle);
            if (cycle == NULL) {
                cycle = (ngx_cycle_t *) ngx_cycle;
                continue;
            }
 
            ngx_cycle = cycle;
            ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx,
                                                   ngx_core_module);
            ngx_start_worker_processes(cycle, ccf->worker_processes,
                                       NGX_PROCESS_JUST_RESPAWN);
            ngx_start_cache_manager_processes(cycle, 1);
            live = 1;
            ngx_signal_worker_processes(cycle,
                                        ngx_signal_value(NGX_SHUTDOWN_SIGNAL));
        }

        if (ngx_restart) {
            ngx_restart = 0;
            ngx_start_worker_processes(cycle, ccf->worker_processes,
                                       NGX_PROCESS_RESPAWN);
            ngx_start_cache_manager_processes(cycle, 0);
            live = 1;
        }

        if (ngx_reopen) {
            ngx_reopen = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reopening logs");
            ngx_reopen_files(cycle, ccf->user);
            ngx_signal_worker_processes(cycle,
                                        ngx_signal_value(NGX_REOPEN_SIGNAL));
        }

        if (ngx_change_binary) {
            ngx_change_binary = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "changing binary");
            ngx_new_binary = ngx_exec_new_binary(cycle, ngx_argv);
        }

        if (ngx_noaccept) {
            ngx_noaccept = 0;
            ngx_noaccepting = 1;
            ngx_signal_worker_processes(cycle,
                                              ngx_signal_value(NGX_SHUTDOWN_SIGNAL));
        }
~~~

![](https://ask.qcloudimg.com/http-save/yehe-1215266/dkmy8wwqsr.png?imageView2/2/w/1620)

## 三  SRS

我们给出了一个例子，部署了两个源站做集群，还部署了一个边缘

https://github.com/ossrs/srs/wiki/v3_CN_SampleOriginCluster

**SRS边缘配置文件，从多个源站拉流，实现热备和负载均衡。**

https://github.com/ossrs/srs/wiki/v1_CN_Forward



forward也可以用作搭建小型集群。架构图如下：

```
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



## Forward VS Edge

单台服务器做直播，总归有单点风险，利用SRS的[Forward机制][1] + [Edge Server][2]设计，可以很容易搭建一个大规模的高可用集群，

![image.png](https://i.loli.net/2020/02/11/LDydeYKwh8zjtIg.png)



# 参考

- srs集群

  https://chihiro.org.cn/blogs/1651636328.html



[ now ] https://cloud.tencent.com/developer/article/1037784   []

​        https://www.jianshu.com/p/e4acfd06d289

​          https://erpeng.github.io/2019/09/17/NGINX-graceful-stop-or-upgrade/ 

​          http://shzhangji.com/cnblogs/2012/12/23/nginx-live-upgrade/ [ OK]

​         https://blog.csdn.net/chaoren2007113025/article/details/84400105 [ok]





make [upgrade](https://www.centos.bz/tag/upgrade/)

[1] 图解HTTP 第三章 第四章节（第一次看发现全部都是解释字段含义，产生没有什么学的感觉。第二次看http协议格式）c

[2]  https://zhaohuabing.com/istio-practice/ 

