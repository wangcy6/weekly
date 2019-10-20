## **Replication models**

- asynchronous（异步)
- semi-synchronous（半同步） 至少一个ack
- synchronous（同步）



----------------------------------------------------------------------------------

## FQA

1. 只有重启master才能继续恢复这些数据?

​     如果master失效，我们通常的做法是重启master，而不是failover到其他的slave

---------------------------------------------------------------------------------

![1560296774102](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1560296774102.png)