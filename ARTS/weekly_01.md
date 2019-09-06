# GTD践行 2019年第35周报  



### 一周记录

本周最主要的矛盾，也是本月，本年最重要矛盾。

你竟然忍受狭小，挪不步。被挤压肉饼的空间，站着做1小时地铁 拼命精神，
也不愿意早起几分钟。这是战略上懒惰
在床上拖延60分钟里，拿出几分钟就够了。

https://github.com/wangcy6/weekly/issues/17


画外音：历史bug根本没有解决，你说好解决呢

>前面3个月问题重现了
>最近3个月一直为频繁玩手机造成早睡早起精力不足造成消极情绪
>和上班时候只知道不提打开浏览器和印象笔记造成消极情绪
>这2 个问题 停滞不前  



### 一. ARTS


#### 1.Algorithm

每周至少做一个 leetcode 的算法题

[leetcode- 139. 单词拆](https://mp.weixin.qq.com/s/OsdGTbFflKtLngw4YGPCSQ%3C/a%3E)

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

[全文解析](ttps://mp.weixin.qq.com/s/OsdGTbFflKtLngw4YGPCSQ%3C/a%3E)

图片描述：如下



![image.png](https://upload-images.jianshu.io/upload_images/1837968-3e290903e31b0259.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![image.png](https://upload-images.jianshu.io/upload_images/1837968-325bb26b147d0afa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![image.png](https://upload-images.jianshu.io/upload_images/1837968-1ea0b1a0c2c3ac74.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

摘要：

> 字符字符串s假如拆分s1和s2 。
> 如果s1和s2都存在 最完美了，结束。
> 如果s1和s2都不存在，如何继续判断呢？
> 动态规划采用的是 不断拆分前缀s1，
> 直到遇到匹配的s2
> 回朔采用的不断拆分后缀s2,直到遇到匹配的s1减少递归次数。
> 想法1 是通过无记忆回朔方式，直接超时
> 想法2 是通过有记忆回朔方式想法3  是通过动态规划方式

考虑最复杂情况是什么，

时间复杂度：O(n^n)  考虑最坏情况 s = {aaaaaaa} 。每一个前缀都在字典中，此时回溯树的复杂度会达到 n^n
必须采用有记忆的方法



#### 2.Review 阅读 点评 英文技术文章

#### 2.1 阅读英文技术文档1篇


1. [分布式基础概念--线性一致性和顺序一致性](linearizability-versus-serializability)
              

- 图片描述：如下



![image.png](https://upload-images.jianshu.io/upload_images/1837968-b5db1a915457d3e6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 摘要

线性一致性保证单个操作，单个对象，在时间是读写顺序，读取记录一定是最新记录

  顺序一致性在时间上没有这个要求，保证一组事物，多个对象的操作一致性。

   这需要2个基本改变，CAP的C和AICD C不是同一个概念，前者 修改复制，后者是原子性。

2. [Raft论文阅读](https://raft.github.io/)

  后面整理成文章 。

- 摘要

 故障发生后，为了维持数据的一致性，raft并没有恢复期概念，如果选举新的领导就可以直接对外服务了。

- 图片描述：如下

![image.png](https://upload-images.jianshu.io/upload_images/1837968-09973096a6aa6ce2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image.png](https://upload-images.jianshu.io/upload_images/1837968-09973096a6aa6ce2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image.png](https://upload-images.jianshu.io/upload_images/1837968-d8ed6ecb3b470365.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 3. Tip：学习至少一个技术技巧

  [意志力实验：直面自身欲望，但是不要付诸行定](https://mp.weixin.qq.com/s/Bg-a2W5_4OyR9hhy3Y6ptQ)

接下来一周里可以用以下 4个步骤来应对自己强烈的欲望 。这些欲望可以是巧克力 、卡布奇诺咖啡或不停查收电子邮件 。
1 ．承认自己脑海中的欲望 ，以及渴望某种事物的感觉 。
2 ．不要马上试着转移注意力或与之争论 。接受这种想法或感觉 ，提醒自己 “白熊 ”现象和 “反弹 ”理论 。
3 ．退一步考虑 ，意识到这种想法和感觉并不受你控制 ，但你可以选择是否将这些想法付诸实践 。
4 ．记住你的目标 ，提醒自己预先作出的承诺 。正如那些学生会提醒自己 ，他们答应过不偷吃巧克力 。

这个需要反复练习


#### 4.  Share


#### 4.1 分享一篇有思考的技术文章


 上文

- 文章：[单机100w连接（C1000K）是如何达成的](https://www.jianshu.com/p/e0b52dc702d6)

c1000k TCP 连接上限测试
https://github.com/wangcy6/c1000k

摘要：
百万连接不消耗，服务器的百万端口，但是消耗百万文件句柄。

1. Linux最大文件数限制 65w
sysctl fs.file-max
fs.file-max = 655360



 #### 4.2 分享一篇有观点文章 

后面整理一个文章。

“如何挣到一千万？

那起床举例子

- 发现自己每天起床很晚，耽误事情，尝试去早起------不是说一定早起
- 发现很难，于是看更多相关书籍和总结 -----不一定做好
- 对比别人根本不需要努力就早起，怎么办 继续学习-不一定有成绩
- 最终发现 早起不是懒惰 是工作安排 方向很大关系- --不一定从根本上解决问题，你能力上
- 早起是习惯 不消耗意志力，方法来解决。----提高认知

![image.png](https://upload-images.jianshu.io/upload_images/1837968-48196c4bb9689cd9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)








### 二 . 起床-运动-阅读 执行情况跟踪


#### 1. 起床习惯--没有记录就没有进步
- 睡眠：

  > 一周内 6点起床早起0次，，本月早起 3次，本年早起10次，
  >
  > 
  >
  > 画外音：
  >
  >  一 夜回到解放前，一次早起 你得意忘形，好了伤疤，忘记痛，后面出现几个月晚起。
  >
  > 这个周期太危险了

- 鼠标点击：

> 电脑 平均每天点击鼠标6167次 39秒点击1次
>
> 
>
> 画外音：
>
> 忙碌到没有时间思考。就是下忙碌，你目标呢 你机会呢，全部没有
> 



- 手机  一周5天，你2天在玩手机 

  吃饭看手机，睡觉看手机，地铁看手机，躺在床上看手机。

  

  画外音：

  小白鼠实验就是你呀

![image.png](https://upload-images.jianshu.io/upload_images/1837968-89a062bf2538830a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 运动习惯--改变的开始
问题：发现自己眼中驼背 ，高低肩  这是不正确坐姿，紧张引起的。

本周运动情况0 ，本月运动情况 0 ，一个字惨。



画外音：

运动不需要手机记录，直接跑步就行了。






#### 3.  阅读进展 ---科学合理方法

> 阅读完毕跑步圣经（40%），
>
> 就记住一句话 跑步的时候你就是上帝，跑步很多技巧，拉伸等准备，这驼背 结合起来

画外音：

掌控跑步，你掌控生活。

#### 三 .下周计划 -吃饭的饭碗

- 本周执行力不够

![image.png](https://upload-images.jianshu.io/upload_images/1837968-dd62d2988cbf3043.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 本周目标不清楚

  ![image.png](https://upload-images.jianshu.io/upload_images/1837968-32fc60f91601e310.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)