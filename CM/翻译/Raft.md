
### raft相关 资源 
官方：https://raft.github.io/

英文：https://raft.github.io/raft.pdf

中文：https://destinywang.github.io/blog/2018/04/15/%E7%BF%BB%E8%AF%91-In-Search-of-an-Understandable-Consensus-Algorithm-%E2%80%94%E2%80%94-Raft%E7%AE%97%E6%B3%95/

视频 
https://www.youtube.com/watch?v=YbZ3zDzDnrw
https://www.youtube.com/watch?v=vYp4LYbnnW8&feature=youtu.be

书籍：http://book.mixu.net/distsys/replication.html
动画：http://thesecretlivesofdata.com/raft/

其他



本篇博客为著名的 RAFT 一致性算法论文的中文翻译，论文名为《In search of an Understandable Consensus Algorithm (Extended Version)》(寻找一种易于理解的一致性算法)

Raft 是一种用来管理日志复制的一致性算法。它和 Paxos 的性能和功能是一样的，但是它和 Paxos 的结构不一样；这使得 Raft 更容易理解并且更易于建立实际的系统。为了提高理解性，Raft 将一致性算法分为了几个部分，例如领导选取（leader selection），日志复制（log replication）和安全性（safety），同时它使用了更强的一致性来减少了必须需要考虑的状态。从用户学习的结果来看，Raft 比 Paxos 更容易学会。Raft 还包括了一种新的机制来使得动态改变集群成员，它使用重叠大多数（overlapping majorities）来保证安全。

### 1. 引言
一致性算法允许一组机器像一个整体一样工作，即使其中的一些机器出了错误也能正常工作。正因为此，他们扮演着建立大规模可靠的软件系统的关键角色。在过去的十年中 Paxos 一直都主导着有关一致性算法的讨论：大多数一致性算法的实现都基于它或者受它影响，并且 Paxos 也成为了教学生关于一致性知识的主要工具。

Consensus algorithms allow a collection of machines
to work as a coherent group that can survive the failures of some of its members. Because of this, they play a
key role in building reliable large-scale software systems.
Paxos  has dominated the discussion of consensus algorithms over the last decade: most implementations
of consensus are based on Paxos or influenced by it, and
Paxos has become the primary vehicle used to teach students about consensus.

不幸的是，尽管在降低它的复杂性方面做了许多努力，Paxos 依旧很难理解。并且，Paxos 需要经过复杂的修改才能应用于实际中。这些导致了系统构构建者和学生都十分头疼。

Unfortunately, Paxos is quite difficult to understand, in
spite of numerous attempts to make it more approachable.
Furthermore, its architecture requires complex changes
to support practical systems. As a result, both system
builders and students struggle with Paxos.


在被 Paxos 折磨之后，我们开始寻找一种在系统构建和教学上更好的新的一致性算法。我们的首要目标是让它易于理解：我们能不能定义一种面向实际系统的一致性算法并且比 Paxos 更容易学习呢？并且，我们希望这种算法能凭直觉就能明白，这对于一个系统构建者来说是十分必要的。对于一个算法，不仅仅是让它工作起来很重要，知道它是如何工作的更重要。

after a new consensus algorithm that could provide a better foundation for system building and education. Our approach was unusual in that our primary goal was understandability: could we define a consensus algorithm for
practical systems and describe it in a way that is significantly easier to learn than Paxos? Furthermore, we wanted
the algorithm to facilitate the development of intuitions
that are essential for system builders. It was important not
just for the algorithm to work, but for it to be obvious why
it works


我们工作的结果是一种新的一致性算法，叫做 Raft。在设计 Raft 的过程中我们应用了许多专门的技巧来提升理解性，包括算法分解（分为领导选取（leader selection），日志复制（log replication）和安全性（safety）） 和 减少状态（state space reduction）（相对于 Paxos，Raft 减少了非确定性的程度和服务器互相不一致的方式）。在两所学校的43个学生的研究中发现，Raft 比 Paxos 要更容易理解：在学习了两种算法之后，其中的33个学生回答 Raft 的问题要比回答 Paxos 的问题要好。

在许多方面，Raft与现有的协商一致意见相似(最值得注意的是，Oki和Liskov的Viewstamped复制)，但它有几个新的特点:


- 强领导者（Strong Leader） : 

Raft使用一种比其他共识算法更强的领导方式。
例如，日志条目只从Leader流向其他服务器。这样就简化了复制日志的管理，使Raft更容易理解。

Raft uses a stronger form of leadership than other consensus algorithms.
 For example,
log entries only flow from the leader to other servers.
This simplifies the management of the replicated log
and makes Raft easier to understand.




- 领导选取（Leader Selection）:
 Raft 使用随机定时器选举领导人。这只增加了对任何协商一致算法所需的心跳的一小部分机制，同时快速地解决冲突。
(不需要提前配置好)

Raft uses randomized timers to
elect leaders. This adds only a small amount of
mechanism to the heartbeats already required for any
consensus algorithm, while resolving conflicts simply and rapidly.


- 成员变化（Membership Change）:

 Raft 为了调整集群中成员关系使用了新的联合一致性（joint consensus）的方法，这种方法中大多数不同配置的机器在转换关系的时候会交迭（overlap）。这使得在配置改变的时候，集群能够继续操作。

 Raft’s mechanism for
changing the set of servers in the cluster uses a new
joint consensus approach where the majorities of
two different configurations overlap during transitions. This allows the cluster to continue operating
normally during configuration changes


我们认为，Raft 在教学方面和实际实现方面比 Paxos 和其他算法更出众。

它比其他算法更简单、更容易理解；
它能满足一个实际系统的需求；
它拥有许多开源的实现并且被许多公司所使用；
它的安全特性已经被证明；
并且它的效率和其他算法相比也具有竞争力。


这篇论文剩下的部分会讲如下内容：

复制状态机（replicated state machine）问题（第2节）;

讨论 Paxos 的优缺点（第3节）;

讨论我们用的为了达到提升理解性的方法（第4节）;

陈述 Raft 一致性算法（第5~8节）;

评价 Raft 算法（第9节）;

对相关工作的讨论（第10节）。

The remainder of the paper introduces the replicated
state machine problem (Section 2), discusses the strengths
and weaknesses of Paxos (Section 3), describes our general approach to understandability (Section 4), presents
the Raft consensus algorithm (Sections 5–8), evaluates
Raft (Section 9), and discusses related work (Section 10).

###  2. 复制状态机（Replicated State Machine）

复制状态机在分布式领域是一个常用且重要的技术。
通过复制服务副本，并和副本一起来协调客户端的交互，来实现容错服务。
这个方法同样提供了一个框架，来理解和设计复制管理协议。
一致性算法是在复制状态机的背景下提出来的。在这个方法中，在一组服务器的状态机产生同样的状态的副本因此即使有一些服务器崩溃了这组服务器也还能继续执行。

复制状态机在分布式系统中被用于解决许多有关容错的问题。例如，GFS，HDFS还有 RAMCloud 这些大规模的系统都是用一个单独的集群领导者，使用一个单独的复制状态机来进行领导选取和存储配置信息来应对领导者的崩溃。使用复制状态机的例子有 Chubby 和 ZooKeeper。

复制状态机的架构。一致性算法管理来自客户端状态命令的复制日志。状态机处理的日志中的命令的顺序都是一致的，因此会得到相同的执行结果。



复制状态机是通过复制日志来实现的。每一台服务器保存着一份日志，日志中包含一系列的命令，状态机会按顺序执行这些命令。因为每一台计算机的状态机都是确定的，所以每个状态机的状态都是相同的，执行的命令是相同的，最后的执行结果也就是一样的了。

Replicated state machines are typically implemented
using a replicated log, as shown in Figure 1. 
![log](https://upload-images.jianshu.io/upload_images/1837968-8b8d8df72ca9f2ea.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


如何保证复制日志一致就是一致性算法的工作了。

在一台服务器上，一致性模块接受客户端的命令并且把命令加入到它的日志中。

它和其他服务器上的一致性模块进行通信来确保每一个日志最终包含相同序列的请求，即使有一些服务器宕机了。
一旦这些命令被正确的复制了，每一个服务器的状态机都会按同样的顺序去执行它们，然后将结果返回给客户端。

最终，这些服务器看起来就像一台可靠的状态机。

Keeping the replicated log consistent is the job of the
consensus algorithm. The consensus module on a server
receives commands from clients and adds them to its log.
It communicates with the consensus modules on other
servers to ensure that every log eventually contains the
same requests in the same order, even if some servers fail.
Once commands are properly replicated, each server’s
state machine processes them in log order, and the outputs are returned to clients. As a result, the servers appear
to form a single, highly reliable state machine


应用于实际系统的一致性算法一般有以下特性：
- ensure safety

确保安全性（从来不会返回一个错误的结果），即使在所有的非拜占庭（Non-Byzantine）情况下，包括网络延迟、分区、丢包、冗余和乱序的情况下。
- available

高可用性，只要集群中的大部分机器都能运行，可以互相通信并且可以和客户端通信，这个集群就可用。
因此，一般来说，一个拥有 5 台机器的集群可以容忍其中的 2 台的失败（fail）。服务器停止工作了我们就认为它失败（fail）了，没准一会当它们拥有稳定的存储时就能从中恢复过来，重新加入到集群中。

>They are fully functional (available) as long as any
**majority of the servers are operational** and can communicate with each other and with clients. 

Thus, a typical cluster of five servers can tolerate the failure
of any two servers. Servers are assumed to fail by
stopping; they may later recover from state on stable
storage and rejoin the cluster


不依赖时序保证一致性，时钟错误和极端情况下的消息延迟在最坏的情况下才会引起可用性问题。


通常情况下，一条命令能够尽可能快的在大多数节点对一轮远程调用作出相应时完成，一少部分慢的机器不会影响系统的整体性能。


#### 3. Paxos算法的不足
    What’s wrong with Paxos?

在过去的10年中，Leslie Lamport 的 Paxos 算法几乎已经成为了一致性算法的代名词：它是授课中最常见的算法，同时也是许多一致性算法实现的起点。Paxos 首先定义了一个能够达成单一决策一致的协议，例如一个单一复制日志条目（single replicated log entry）。我们把这个子集叫做单一决策 Paxos（single-decree Paxos）。之后 Paxos通过组合多个这种协议来完成一系列的决策，例如一个日志（multi-Paxos）。Paxos 确保安全性和活跃性（liveness），并且它支持集群成员的变更。它的正确性已经被证明，通常情况下也很高效。

不幸的是，Paxos 有两个致命的缺点。
Unfortunately, Paxos has two significant drawbacks

Paxos 太难以理解。它的完整的解释晦涩难懂；很少有人能完全理解，只有少数人成功的读懂了它。并且大家做了许多努力来用一些简单的术语来描述它。尽管这些解释都关注于单一决策子集问题，但仍具有挑战性。在 NSDI 2012 会议上的一次非正式调查显示，我们发现大家对 Paxos 都感到不满意，其中甚至包括一些有经验的研究员。我们自己也曾深陷其中，我们在读过几篇简化它的文章并且设计了我们自己的算法之后才完全理解了 Paxos，而整个过程花费了将近一年的时间。

我们假定 Paxos 的晦涩来源于它将单决策子集作为它的基础。单决策（Single-decree）Paxos 是晦涩且微妙的：它被划分为两个没有简单直观解释的阶段，并且难以独立理解。正因为如此，它不能很直观的让我们知道为什么单一决策协议能够工作。为多决策 Paxos 设计的规则又添加了额外的复杂性和精巧性。我们相信多决策问题能够分解为其它更直观的方式。

它难以在实际环境中实现。其中一个原因是，对于多决策 Paxos （multi-Paxos） ，大家还没有一个一致同意的算法。Lamport 的描述大部分都是有关于单决策 Paxos （single-decree Paxos）；他仅仅描述了实现多决策的可能的方法，缺少许多细节。有许多实现 Paxos 和优化 Paxos 的尝试，但是他们都和 Lamport 的描述有些出入。例如，Chubby 实现的是一个类似 Paxos 的算法，但是在许多情况下的细节没有公开。

另外，Paxos 的结构也是不容易在一个实际系统中进行实现的，这是单决策问题分解带来的又一个问题。例如，从许多日志条目中选出条目然后把它们融合到一个序列化的日志中并没有带来什么好处，它仅仅增加了复杂性。围绕着日志来设计一个系统是更简单、更高效的：新日志按照严格的顺序添加到日志中去。另一个问题是，Paxos 使用对等的点对点的实现作为它的核心（尽管它最终提出了一种弱领导者的形式来优化性能）。这种方法在只有一个决策被制定的情况下才显得有效，但是很少有现实中的系统使用它。如果要做许多的决策，选择一个领导人，由领带人来协调是更简单有效的方法。

因此，在实际的系统应用中和 Paxos 算法都相差很大。所有开始于 Paxos 的实现都会遇到很多问题，然后由此衍生出了许多与 Paxos 有很大不同的架构。这是既费时又容易出错的，并且理解 Paxos 的难度又非常大。Paxos 算法在它正确性的理论证明上是很好的，但是在实现上的价值就远远不足了。来自 Chubby 的实现的一条评论就能够说明：

There are signiﬁcant gaps between the description of the Paxos algorithm and the needs of a real-world system...
the ﬁnal system will be based on an unproven protocol

翻译：Paxos 算法的描述与实际实现之间存在巨大的鸿沟...
最终的系统往往建立在一个没有被证明的算法之上。
正因为存在这些问题，我们认为 Paxos 不仅对于系统的构建者来说不友好，同时也不利于教学。鉴于一致性算法对于大规模软件系统的重要性，我们决定试着来设计一种另外的比 Paxos 更好的一致性算法。Raft 就是这样的一个算法。

### 4. 易于理解的设计
     Designing for understandability

设计 Raft 的目标有如下几个：

1. 它必须提供一个完整的、实际的基础来进行系统构建，为的是减少开发者的工作；
它必须在所有情况下都能保证安全可用；
它对于常规操作必须高效；

We had several goals in designing Raft: it must provide
a complete and practical foundation for system building,
so that it significantly reduces the amount of design work
required of developers;

2 ,最重要的目标是：易于理解，它必须使得大多数人能够很容易的理解；

3. 另外，它必须能让开发者有一个直观的认识，这样才能使系统构建者们去对它进行扩展。

在设计 Raft 的过程中，我们不得不在许多种方法中做出选择。当面临这种情况时，我们通常会权衡可理解性：
每种方法的可理解性是如何的？（例如，它的状态空间有多复杂？它是不是有很细微的含义？）它的可读性如何？读者能不能轻易地理解这个方法和它的含义？

我们意识到对这种可理解性的分析具有高度的主观性；尽管如此，我们使用了两种适用的方式。

>第一种是众所周知的问题分解：

我们尽可能将问题分解成为若干个可解决的、可被理解的小问题。例如，在 Raft 中，我们把问题分解成为了
领导选取（leader election）、
日志复制（log replication）、
安全（safety）
和成员变化（membership changes）。

>我们采用的第二个方法是通过减少需要考虑的状态的数量将状态空间简化，
这能够使得整个系统更加一致并且尽可能消除不确定性。特别地，日志之间不允许出现空洞，并且 Raft 限制了限制了日志不一致的可能性。尽管在大多数情况下，我们都都在试图消除不确定性，但是有时候有些情况下，不确定性使得算法更易理解。尤其是，随机化方法使得不确定性增加，但是它减少了状态空间。我们使用随机化来简化了 Raft 中的领导选取算法。


### 5. Raft 一致性算法 The Raft consensus algorithm
Raft是一种用于管理第2节中描述的表单的复制日志的算法。表2总结了压缩格式的算法，
表3列出了算法的关键属性;这些数字的组成部分是分段讨论的。

状态
表-2-1
在所有服务器上持久存在的
名称	描述
currentTerm	服务器最后知道的任期号（从0开始递增）
votedFor	当前任期内收到选票的 候选人 id（如果没有就为null）
log[]	日志条目；，诶个条目包含状态机的要执行命令和从 `领导者 出收到的任期号
在所有服务器上不稳定存在的
名称	描述
commitIndex	已知的被提交的最大日志条目的索引值（从0开始递增）
lastApplied	被状态机执行的额最大日志条目的索引值（从0开始递增）
在领导人服务器上不稳定存在的（在选举之后初始化的）
名称	描述
nextIndex[]	对于每个服务器，记录需要发给它的下一个日志条目的索引（初始化为Leader上一条日志索引+1）
natchIndex[]	对于每一个服务器，记录已经复制到该拂去其的日志的最高索引值（从0开始递增）
附加日志远程调用（AppendEntries RPC）
由领导人来调用复制日志

![image.png](https://upload-images.jianshu.io/upload_images/1837968-bb5dcd103b1ce624.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
表-2-2
~~~
参数	描述
term	领导人的任期号
leaderId	领导人的id，为了其他服务器能重定向到Leader

prevLogIndex	最新日志之前的日志的索引值
prevLogTerm	最新日志之前的日志的领导人任期号
entries[]	要存储的日志条目（表示heartbeat时为空，有时会为了效率发送多条）
leaderCommit	领导人提交的日志条目索引值
返回值	描述
term	当前的任期号，用于 Leader 更新自己的任期号
success	如果其他服务器包含能够匹配上 prevLogIndex 和 prevLogTerm 的日志时为真
Follower需要实现：

如果 term < currentTerm 返回false
如果在 prevLogIndex 处的日志的任期号与 prevLogTerm 不匹配时，返回false
如果一条已经存在的日志与新的冲突（index 相同但任期号 term 不同），则删除已经存在的日志和它之后的所有日志
添加任何在以后日志中不存在的条目
如果 leaderCommit > commitIndex，将 commitIndex 设置为 leaderCommit 和最新日志条目索引号中较小的一个

~~~

- 投票请求RPC（RequestVote RPC）
  由候选人发起收集选票


![image.png](https://upload-images.jianshu.io/upload_images/1837968-c92f43a732c64139.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

~~~
表-2-3
参数	描述
term	领导人的任期号
candidateId	请求投票的候选人id
lastLogIndex	候选人最新日志条目的索引值
lastLogTerm	     候选人最新日志条目对应的任期号
返回值	描述
term	当前的任期号，用于 候选人 更新自己的任期号
voteGranted	如果候选人收到选票为true
接受者需要实现

如果 term < currentTerm 返回false
如果 votedFor 为空或者与 candidateId 相同，并且候选人的日志和自己的日志一样新，则给候选人投票。
~~~

- 服务器需要遵守的规则

所有服务器
如果 commitIndex > lastApplied，lastApplied 自增，将 log[lastApplied] 应用到状态机；
如果RPC的请求或者响应中包含一个 Term > currentTerm，则 currentTerm 赋值为 Term，并切换状态为Follower；
Follower
响应来自候选人和领导人的RPC请求
如果在超过选取 Leader 时间之前没有收到来自领导人的 AppendEntries RPC 或者没有收到候选人的投票请求，则自己转换状态为候选人
Candidate
转变为 Candidate 之后开始选举
currentTerm 自增
给自己投票
重置选举计时器
向其他服务器发送 RequestVote RPC
如果收到了来自大多数服务器的投票，则成为领导人
如果收到了来自新 Leader 的 AppendEntries RPC(heartbeat)，则成为 Follower
如果选举超时，开始新一轮选举
Leader
一旦成为领导人：想起他所有服务器发送空的 AppendEntries PRC(heartbeat)；在空闲时间重复发送以防止选举超时
如果收到来自客户端的请求，向本地日子增加条目，在该条目应用到状态机后响应客户端
对于一个 Followed 来说，如果上一次收到的日志索引大于将要收到的日志索引(nextIndex)：通过 AppendEntries RPC 将 nextIndex 之后的所有日志条目发送出去
如果发送成功：将该 Follower 的 nextIndex 和 matchIndex 更新
如果由于日志不一致导致 AppendEntries RPC 失败：nextIndex 递减并且重新发送
如果存在一个满足 N > commitIndex 和 matchIndex[i] >= N 并且 log[N].term == currentTerm的 N，则将 commitIndex 赋值为N
Raft 一致性算法的总结（不包括成员变化和日志压缩）
表-3 Raft 算法保证这些特性任何时刻都能成立
性质	描述
选举安全原则(Election Safety)	一个任期 (Term) 内最多允许有一个 Leader 被选上
领导者只增加原则(Leader Append-Only)	Leader 永远不会覆盖或删除自己的日志，只会增加条目
日志匹配原则(Log Matching)	如果两个日志在相同的索引位置上的日志条目的任期号相同，那么我们就认为这个日志从头到这个索引位置的条目完全相同。
领导者完全原则(Leader Completeness)	如果一个日志条目在一个给定任期内被提交，那么这个条目一定会出现在所有任期更大的 Leader 中
状态机安全原则(State Machine Safely)	如果一个服务器已经将给定索引位置的日志条目应用到状态机中，则所有其他服务器不会在该索引位置应用不同的条目
Raft 通过首先选出一个领导人来实现一致性，然后给予领导人完全管理复制日志（replicated log）的责任。领导人接收来自客户端的日志条目，并把它们复制到其他的服务器上，领带人还要告诉服务器们什么时候将日志条目应用到它们的状态机是安全的。通过选出领导人能够简化复制日志的管理工作。例如，领导人能够决定将新的日志条目放到哪，而并不需要和其他的服务器商议，数据流被简化成从领导人流向其他服务器。如果领导人宕机或者和其他服务器失去连接，就可以选取下一个领导人。

通过选出 Leader 的方法，Raft 将共识问题分解为三个相对独立的子问题，这些子问题在下面的子部分中讨论:

Leader 选举: 当现有 Leader 失败时，必须选出新的 Leader。
日志复制（Log replication）： 领导人必须从客户端接收日志然后复制到集群中的其他服务器，并且强制要求其他服务器的日志保持和自己相同
安全性（Safety）： Raft 的关键的安全特性是 表-3 中提到的状态机安全原则（State Machine Safety）:如果一个服务器已经将给定索引位置的日志条目应用到状态机中，则所有其他服务器不会在该索引位置应用不同的条目。
5.4节阐述了 Raft 是如何保证这条原则的，解决方案涉及到一个对于选举机制另外的限制，这一部分会在 5.2节 中说明。
在说明了一致性算法之后，本章会讨论有关可用性（availability）的问题和系统中时序（timing）的问题。

5.1. Raft基础  Raft basics

一个 Raft 集群包括若干服务器；对于一个典型的 5 服务器集群，该集群能够容忍 2 台机器不能正常工作，而整个系统保持正常。

A Raft cluster contains several servers; 
five is a typical number, which allows the system to tolerate two failures

在任意的时间，每一个服务器一定会处于以下三种状态中的一个：
领导人、候选人、追随者。
在正常情况下，只有一个服务器是领导人，剩下的服务器是追随者。追随者们是被动的：他们不会发送任何请求，只是响应来自领导人和候选人的请求。

领导人来处理所有来自客户端的请求（如果一个客户端与追随者进行通信，追随者会将信息发送给领导人）。
候选人是用来选取一个新的领导人的，这一部分会在 5.2节 进行阐释。图-4 阐述了这些状态，和它们之间的转换；它们的转换会在下边进行讨论。


服务器的状态。追随者只响应其他服务器的请求。如果追随者没有收到任何消息，它会成为一个候选人并且开始一次选举。收到大多数服务器投票的候选人会成为新的领导人。领导人在它们宕机之前会一直保持领导人的状态。


时间被分为一个个的任期（term），每一个任期的开始都是领导人选举。在成功选举之后，一个领导人会在任期内管理整个集群。如果选举失败，该任期就会因为没有领带人而结束。这个转变会在不同的时间的不同服务器上观察到。

![image.png](https://upload-images.jianshu.io/upload_images/1837968-e302465d818aef26.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如 图-5 所示，Raft 算法将时间划分成为任意不同长度的 任期（term）。任期用连续的数字进行表示。每一个任期的开始都是一次选举（election），
就像 5.2 节 所描述的那样，一个或多个候选人会试图成为领导人。如果一个候选人赢得了选举，它就会在该任期的剩余时间担任领导人。
在某些情况下，选票会被瓜分，有可能没有选出领导人，那么，将会开始另一个任期，并且立刻开始下一次选举。Raft 算法保证在给定的一个任期最少要有一个领导人。

不同的服务器可能会在任期内观察到多次不同的状态转换，在某些情况下，一台服务器可能看不到一次选举或者一个完整的任期。任期在 Raft 中充当逻辑时钟的角色，并且它们允许服务器检测过期的信息，比如过时的领导人。每一台服务器都存储着一个当前任期的数字，这个数字会单调的增加。当服务器之间进行通信时，会互相交换当前任期号；如果一台服务器的当前任期号比其它服务器的小，则更新为较大的任期号。如果一个候选人或者领导人意识到它的任期号过时了，它会立刻转换为追随者状态。如果一台服务器收到的请求的任期号是过时的，那么它会拒绝此次请求。

Raft 中的服务器通过远程过程调用（RPC）来通信，基本的 Raft 一致性算法仅需要 2 种 RPC。RequestVote RPC 是候选人在选举过程中触发的（5.2节），AppendEntries RPC 是领导人触发的，为的是复制日志条目和提供一种 心跳（heartbeat） 机制（5.3节）。第7章加入了第三种 RPC 来在各个服务器之间传输 快照（snapshot）。如果服务器没有及时收到 RPC 的响应，它们会重试，并且它们能够并行的发出 RPC 来获得最好的性能。

5.2. 领导人选举
Raft 使用一种 心跳机制（heartbeat） 来触发领导人的选取。当服务器启动时，它们会初始化为追随者。一太服务器会一直保持追随者的状态只要它们能够收到来自领导人或者候选人的有效 RPC。领导人会向所有追随者周期性发送 心跳（heartbeat，不带有任何日志条目的 AppendEntries RPC） 来保证它们的领导人地位。如果一个追随者在一个周期内没有收到心跳信息，就叫做 选举超时（election timeout） ,然后它就会假定没有可用的领导人并且开始一次选举来选出一个新的领导人。

为了开始选举，一个追随者会自增它的当前任期并且转换状态为候选人。然后，它会给自己投票并且给集群中的其他服务器发送 RequestVote RPC 。一个候选人会一直处于该状态，直到下列三种情形之一发生：

它赢得了选举；
另一台服务器赢得了选举；
一段时间后没有任何一台服务器赢得了选举
一个候选人如果在一个任期内收到了来自集群中大多数服务器的投票就会赢得选举。在一个任期内，一台服务器最多能给一个候选人投票，按照 先到先服务原则（first-come-first-served） （注意：在 5.4节 针对投票添加了一个额外的限制）。大多数原则使得在一个任期内最多有一个候选人能赢得选举 （表-3 中提到的选举安全原则） 。一旦有一个候选人赢得了选举，它就会成为 领导人 。然后它会像其他服务器发送心跳信息来建立自己的领导地位并且组织新的选举。

当一个 候选人 等待别人的选票时，它有可能会收到来自其他服务器发来的声明其为领导人的 AppendEntries RPC 。如果这个领导人的 任期（包含在它的 RPC 中） 比当前候选人的当前任期要大，则候选人认为该领导人合法，并且转换自己的状态为 追随者 。如果在这个 RPC 中的任期小于候选人的当前任期，则候选人会拒绝此次 RPC， 继续保持候选人 状态。

第三种情形是一个 候选人 既没有赢得选举也没有输掉选举：如果许多追随者在同一时刻都成为了候选人，选票会被分散，可能没有候选人能获得大多数的选票。当这种情形发生时，每一个候选人都会超时，并且通过自增任期号和发起另一轮 RequestVote RPC 来开始新的选举。然而，如果没有其它手段来分配选票的话，这种情形可能会无限的重复下去。

Raft 使用 随机的选举超时时间 来确保第三种情形很少发生，并且能够快速解决。为了防止在一开始是选票就被瓜分，选举超时时间是在一个固定的间隔内随机选出来的（例如，150~300ms）。这种机制使得在大多数情况下只有一个服务器会率先超时，它会在其它服务器超时之前赢得选举并且向其它服务器发送心跳信息。同样的机制被用于选票一开始被瓜分的情况下。每一个候选人在开始一次选举的时候会重置一个随机的选举超时时间，在超时进行下一次选举之前一直等待。这能够减小在新的选举中一开始选票就被瓜分的可能性。9.3节 展示了这种方法能够快速的选出一个领导人。

选举是一个理解性引导我们设计替代算法的一个例子。最开始时，我们计划使用一种排名系统：给每一个候选人分配一个唯一的排名，用于在竞争的候选人之中选择领导人。如果一个候选人发现了另一个比它排名高的候选人，那么它会回到追随者的状态，这样排名高的候选人会很容易地赢得选举。但是我们发现这种方法在可用性方面有一点问题（一个低排名的服务器在高排名的服务器宕机后，需要等待超时才能再次成为候选人，但是如果它这么做的太快，它能重置选举领带人的过程）。我们对这个算法做了多次调整，但是每次调整后都会出现一些新的问题。最终我们认为随机重试的方法是更明确并且更易于理解的。

### 5.3.日志复制 Log replication
一旦选出了领导人，它就开始接收客户端的请求。
Once a leader has been elected, it begins servicing
client requests

每一个客户端请求都包含一条需要被 复制状态机（replicated state machine） 执行的命令。领导人把这条命令作为新的日志条目加入到它的日志中去，然后并行的向其他服务器发起 AppendEntries RPC ，要求其它服务器复制这个条目。当这个条目被安全的复制之后（下面的部分会详细阐述），领导人会将这个条目应用到它的状态机中并且会向客户端返回执行结果。

如果追随者崩溃了或者运行缓慢或者是网络丢包了，领导人会无限的重试 AppendEntries RPC （甚至在它向客户端响应之后）知道所有的追随者最终存储了所有的日志条目。
 
 If followers crash or run slowly,
or if network packets are lost, the leader retries AppendEntries RPCs indefinitely (even after it has responded to
the client) until all followers eventually store all log entries.


图-6：日志由有序编号的日志条目组成。每个日志条目包含它被创建时的任期号（每个方块中的数字），并且包含用于状态机执行的命令。如果一个条目能够被状态机安全执行，就被认为可以提交了。

![image.png](https://upload-images.jianshu.io/upload_images/1837968-2f06775f2f95458f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

日志就像 图-6 所示那样组织的。每个日志条目存储着一条被状态机执行的命令和当这条日志条目被领导人接收时的任期号。日志条目中的任期号用来检测在不同服务器上日志的不一致性，并且能确保 图-3 中的一些特性。每个日志条目也包含一个整数索引来表示它在日志中的位置。

领导人 决定什么时候将日志条目应用到状态机是安全的；这种条目被称为 可被提交（commited） 。

 Raft 保证 可被提交（commited）的日志条目 是持久化的并且最终会被所有可用的状态机执行。一旦被领导人创建的条目已经复制到了大多数的服务器上，这个条目就称为可被提交的（例如，图-6中的7号条目）。领导人日志中之前的条目都是可被提交的（commited），包括由之前的领导人创建的条目。5.4节将会讨论当领导人更替之后这条规则的应用问题的细节，并且也讨论了这种提交方式是安全的。领导人跟踪记录它所知道的被提交条目的最大索引值，并且这个索引值会包含在之后的 AppendEntries RPC 中（包括心跳 heartbeat 中），为的是让其他服务器都知道这条条目已经提交。一旦一个追随者知道了一个日志条目已经被提交，它会将该条目应用至本地的状态机（按照日志顺序）。


我们设计了 Raft 日志机制来保证不同服务器上日志的一致性。这样做不仅简化了系统的行为使得它更可预测，并且也是保证安全性不可或缺的一部分。Raft 保证以下特性，并且也保证了 表-3 中的日志匹配原则 （Log Matching Property） :

如果在不同日志中的两个条目有着相同的索引和任期号，则它们所存储的命令是相同的。
如果在不同日志中的两个条目有着相同的索引和任期号，则它们之间的所有条目都是完全一样的。
第一条特性源于 领导人 在一个任期里在给定的一个日志索引位置最多创建一条日志条目，同时该条目在日志中的位置也从来不会改变。第二条特性源于 AppendEntries 的一个简单的一致性检查。当发送一个 AppendEntries RPC 时，领导人会把新日志条目紧接着之前的条目的索引位置和任期号都包含在里面。如果追随者没有在它的日志中找到相同索引和任期号的日志，它就会拒绝新的日志条目。这个一致性检查就像一个归纳步骤：一开始空的日志的状态一定是满足日志匹配原则的，一致性检查保证了当日志添加时的日志匹配原则。因此，只要 AppendEntries 返回成功的时候，领导人就知道追随者们的日志和它的是一致的了。

图-7：当最上边的领导人掌权之后，追随者日志可能有以下情况（a~f）。一个格子表示一个日志条目；格子中的数字是它的任期。一个追随者可能会丢失一些条目（a, b）；可能多出来一些未提交的条目（c, d）；或者两种情况都有（e, f）。例如，场景 f 在如下情况下就会发生：如果一台服务器在任期2时是领导人并且往它的日志中添加了一些条目，然后在将它们提交之前就宕机了，之后它很快重启了，成为了任期3的领导人，又往它的日志中添加了一些条目，然后在任期2和任期3中的条目提交之前它又宕机了并且几个任期内都一直处于宕机状态。

image

在一般情况下， 领导人 和 追随者们 的日志保持一致，因此 AppendEntries 一致性检查通常不会失败。然而， 领导人 的崩溃会导致日志不一致（旧的领导人可能没有完全复制完日志中的所有条目）。这些不一致会导致一系列领导人和追随者崩溃。 图-7 阐述了一些 追随者 可能和 新的领导人 日志不同的情况。一个 追随者 可能会丢失掉领导人上的一些条目，也有可能包含一些 领导人 没有的条目，也有可能两者都会发生。丢失的或者多出来的条目可能会持续多个任期。

在 Raft 算法中， 领导人 通过 强制追随者们复制它的日志 来处理日志的不一致。这就意味着，在追随者上的冲突日志会被领导者的日志覆盖。5.4节会说明当添加了一个额外的限制之后这是安全的。

为了使得追随者的日志同自己的一致， 领导人 需要找到追随者同它的日志一致的地方，然后删除追随者在该位置之后的条目，然后将自己在该位置之后的条目发送给追随者。这些操作都在 AppendEntries RPC 进行一致性检查时完成。领导人给每一个追随者维护了一个 nextIndex ，它表示领导人将要发送给该追随者的下一条日志条目的索引。当一个领导人开始掌权时，它会将 nextIndex 初始化为 它的最新的日志条目索引数+1（图-7 中的 11） 。如果一个追随者的日志和领导者的不一致，AppendEntries 一致性检查会在下一次 AppendEntries RPC 时返回失败。在失败之后，领导人会将 nextIndex 递减然后重试 AppendEntries RPC 。最终 nextIndex 会达到一个领导人和追随者日志一致的地方。这时，AppendEntries 会返回成功，追随者中冲突的日志条目都被移除了，并且添加所缺少的上了领导人的日志条目。一旦 AppendEntries 返回成功，追随者和领导人的日志就一致了，这样的状态会保持到该任期结束。

如果需要的话，算法还可以进行优化来减少 AppendEntries RPC 失败的次数。例如，当拒绝了一个 AppendEntries 请求，追随者可以记录下冲突日志条目的任期号和自己存储那个任期的最早的索引。通过这些信息，领导人能够直接递减nextIndex跨过那个任期内所有的冲突条目；这样的话，一个冲突的任期需要一次 AppendEntries RPC，而不是每一个冲突条目需要一次 AppendEntries RPC。在实践中，我们怀疑这种优化是否是必要的，因为 AppendEntries 一致性检查很少失败并且也不太可能出现大量的日志条目不一致的情况。

通过这种机制，一个领导人在掌权时不需要采取另外特殊的方式来恢复日志的一致性。它只需要使用一些常规的操作，通过响应 AppendEntries 一致性检查的失败能使得日志自动的趋于一致。一个领导人从来不会覆盖或者删除自己的日志（表-3 中的领导人只增加原则）。

这个日志复制机制展示了在第2章中阐述的所希望的一致性特性：Raft 能够接受，复制并且应用新的日志条目只要大部分的服务器是正常的。在通常情况下，一条新的日志条目可以在一轮 RPC 内完成在集群的大多数服务器上的复制；并且一个速度很慢的追随者并不会影响整体的性能。


### FQA
1 客户端如何连接支持raft协议的服务器？

舍去代理方式，随机选择一台机器，redis cluser 就是如此

![舍去代理方式，随机选择一台机器，redis cluser 就是如此](https://upload-images.jianshu.io/upload_images/4236553-3f19933692079d3d.png)

产品级
https://github.com/go-redis/redis
