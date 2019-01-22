## 第一天  redis持久化

几个问题：

1.  写日志文件是多线程吗？如果是 如何保持一致性. 写磁盘文件慢，写内容从快 挤压现象。

2.  恢复日志aof文件是多线程吗？如果保持事物顺序的一致性

3. 写日志文件写一半 然后服务挂掉 改怎么办？

4.  通过buffer io 方式写磁盘 有什么缺点 ，有什么优点？



## 第二天 如何为正在飞行的飞机更换引擎

几个问题：

1. 给你一个key 如何确定在哪个主机上？
2. 如何新增一台机器？
3. 如减少一一台机器？
4. 在没有停机的情况下升级或重新启动Redis实例















塔山

视频：

https://www.youtube.com/watch?v=nFJ7LD-2yXc

文章：

https://redis.io/topics/partitioning

https://www.zhihu.com/question/21419897/answer/89771396

-  分区：如何在多个Redis实例之间拆分数据

​     https://www.jianshu.com/p/dbc62ed27f03

-  数据库秒级平滑扩容架构方案





## 第三天  gperftools 分析redis数据迁移过程

几个问题

-  stl结构数据如何mmap方式保存到文件 （这是操作系统干的事情） 如何解析文件内容呀？




### profiler 

https://gperftools.github.io/gperftools/cpuprofile.html



塔山

move:



https://yq.aliyun.com/articles/64884

https://www.youtube.com/watch?v=Q9MdwzewSZg

doc：

http://www.cnblogs.com/huxiao-tee/p/4660352.html

https://blog.csdn.net/chenxinl/article/details/6679654  内存的数据应到到文件是如何理解

https://blog.csdn.net/lotluck/article/details/81632071

http://www.cppblog.com/lmlf001/archive/2007/09/13/32112.html

 mmap函数实现把一个文件映射到一个内存区域，从而我们可以像读写内存一样读写文件





