

这就是你价值，用不一向的角度回答老问题。

> 别人回答了，那是入门时候，随笔写博客时候，应付项目时候。
>
> 别人迭代了，别人不会重写一本书，一个项目，一个博客纠正。
>
> 别人没有义务纠正你错误。
>
>  你对你认知负责，你需要对你理解负责





## 一、问题



进程和线程区别是什么？



>  你从哪几个角度分析呢，这个范围很广，
>
> 提示:不要被区别字眼限制住，重点什么是线程，在开发中遇到过什么问题。









## 二、你的思考（10秒闪过

> 范围 代码，官方文档 和项目问题 指出内容



#### 1 调度

用户级，内核级，如何切换，一个task从一个cpu队列切换另外一个队列

#### 2.资源销毁。（异常销毁）

最后线程销毁，进程销毁。

3.同步（在1上）(安全)



https://blog.csdn.net/caianye/article/details/5912172

进程和线程都需要锁，不同类型锁。



Pthreads提供了多种锁机制：
(1) Mutex（互斥量）：pthread_mutex_
(2) Spin lock（自旋锁）：pthread_spin_
(3) Condition Variable（条件变量）：pthread_con
(4) Read/Write lock（读写锁）：pthread_rwlock_

[https://zh.wikipedia.org/wiki/%E8%87%AA%E6%97%8B%E9%94%81](https://zh.wikipedia.org/wiki/自旋锁)

Windows操作系统提供的轻型[读写锁](https://zh.wikipedia.org/wiki/读写锁)（SRW Lock）内部就用了自旋锁。显然，单核CPU不适于使用自旋锁



### 思路4

  scalability: *load scalability* and *system scalability*

On the other hand, MP applications have very good system scalability, because no resources are shared among different processes and there is no synchronization overhead.

Driven State Machine Architecture

#### 2.2 Multi-Threaded Architecture

#### 2.1 Multi-Process Architecture

#### 2.3 Event-Driven State Machine Architecture

In the Event-Driven State Machine (EDSM) architecture, a single process is employed to concurrently process multiple connections



Multi-Process EDSM

 Multi-Process EDSM has very good system scalability because no resources are shared among different processes and there is no synchronization overhead.


## 三、你的回答（限制在1分钟，5句话，12秒一句）











## 四、鸡蛋里挑骨头（第一句话回答关键了吗，后面有具体场景吗？或者关键词补充吗）

> 如果简单用法，100%保证不过关，因为没有骨头可挑！
>
> 如果自己强加各种特自己根本不理解很深入原理，你保证100个人 80人也说不出来
>
> 从哪里入手呢？
>
> 1 假如100个人去问，大家都问什么相同的题目。
>
> 2 别看不起官方文档，上面最全面。最正确，包含各种情况（大家关系问题在官方文档有答案）【文档每一行都要看，想当然不行的】
>
> 3 自己手动写小demo







## 五、你自己满意了吗,认为过关了

1. 10秒内单，如果大脑一片空白，对里面里面基础用法（不行）

2. 进一步 提问，原理，异常等毫无总结，（不行）

3. 你必须停下来深入看看看别人怎么做的（学习吧）





## 六、下一个问题是什么（这不是结束，只是一个系统的开始）



## 七、如果自己没有做过类型项目，参考别人经验，自己重新设计，需要考虑知识点是什么？



### 八、如果自己没有做过类型项目，参考别人经验，自己直接写demo，和真是项目最大差距是什么？





## 其他题目



1. 什么是线程？
2. 什么是线程安全和线程不安全？
3. 什么是自旋锁？
4. 什么是Java内存模型？
5. 什么是CAS？
6. 什么是乐观锁和悲观锁？
7. 什么是AQS？
8. 什么是原子操作？在Java Concurrency API中有哪些原子类(atomic classes)？
9. 什么是Executors框架？
10. 什么是阻塞队列？如何使用阻塞队列来实现生产者-消费者模型？
11. 什么是Callable和Future?
12. 什么是FutureTask?
13. 什么是同步容器和并发容器的实现？
14. 什么是多线程？优缺点？
15. 什么是多线程的上下文切换？
16. ThreadLocal的设计理念与作用？
17. ThreadPool（线程池）用法与优势？
18. Concurrent包里的其他东西：ArrayBlockingQueue、CountDownLatch等等。
19. synchronized和ReentrantLock的区别？
20. Semaphore有什么作用？
21. Java Concurrency API中的Lock接口(Lock interface)是什么？对比同步它有什么优势？
22. Hashtable的size()方法中明明只有一条语句”return count”，为什么还要做同步？
23. ConcurrentHashMap的并发度是什么？
24. ReentrantReadWriteLock读写锁的使用？
25. CyclicBarrier和CountDownLatch的用法及区别？
26. LockSupport工具？
27. Condition接口及其实现原理？
28. Fork/Join框架的理解?
29. wait()和sleep()的区别?
30. 线程的五个状态（五种状态，创建、就绪、运行、阻塞和死亡）?
31. start()方法和run()方法的区别？
32. Runnable接口和Callable接口的区别？
33. volatile关键字的作用？
34. Java中如何获取到线程dump文件？
35. 线程和进程有什么区别？
36. 线程实现的方式有几种（四种）？
37. 高并发、任务执行时间短的业务怎样使用线程池？并发不高、任务执行时间长的业务怎样使用线程池？并发高、业务执行时间长的业务怎样使用线程池？
38. 如果你提交任务时，线程池队列已满，这时会发生什么？
39. 锁的等级：方法锁、对象锁、类锁?
40. 如果同步块内的线程抛出异常会发生什么？
41. 并发编程（concurrency）并行编程（parallellism）有什么区别？
42. 如何保证多线程下 i++ 结果正确？
43. 一个线程如果出现了运行时异常会怎么样?
44. 如何在两个线程之间共享数据?
45. 生产者消费者模型的作用是什么?
46. 怎么唤醒一个阻塞的线程?
47. Java中用到的线程调度算法是什么
48. 单例模式的线程安全性?
49. 线程类的构造方法、静态块是被哪个线程调用的?
50. 同步方法和同步块，哪个是更好的选择?
51. 如何检测死锁？怎么预防死锁？