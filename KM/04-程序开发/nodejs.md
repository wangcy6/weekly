# 卡片 

![img](https://segmentfault.com/img/bVO9se?w=822&h=534)



![图片描述](https://segmentfault.com/img/bVyNFf)

https://github.com/nodejs/nodejs.org



# 基础



Node.js 环境搭建(Linux ubuntu 16.10版本)

~~~shell
sudo apt-get install nodejs
sudo apt-get install npm
sudo apt install aptitude
sudo aptitude install npm

root@work:~# node -v 
v8.16.0
root@work:~# npm -v
6.4.1

~~~







# 功能

## event loop

### [nodejs 异步I/O和事件驱动](https://segmentfault.com/a/1190000005173218)

[Node.js](https://nodejs.org/en/) 网站上只有一张插图：[事件循环详解](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick/#event-loop-explained)。如果这是该网站上唯一的图片，那么 Node 团队肯定会认为理解事件循环概念很重要。



```
https://github.com/nodejs/nodejs.org/blob/master/locale/en/docs/guides/event-loop-timers-and-nexttick.md

https://medium.com/@deedee8/event-loop-cycle-in-node-js-bc9dd0f2834f

https://www.ibm.com/developerworks/cn/opensource/os-tutorials-learn-nodejs-the-event-loop/index.html
https://cnodejs.org/topic/5a9108d78d6e16e56bb80882
```



```nginx
   ┌───────────────────────────┐
┌─>│           timers          │
│  └─────────────┬─────────────┘
│  ┌─────────────┴─────────────┐
│  │     pending callbacks     │
│  └─────────────┬─────────────┘
│  ┌─────────────┴─────────────┐
│  │       idle, prepare       │
│  └─────────────┬─────────────┘      ┌───────────────┐
│  ┌─────────────┴─────────────┐      │   incoming:   │
│  │           poll            │<─────┤  connections, │
│  └─────────────┬─────────────┘      │   data, etc.  │
│  ┌─────────────┴─────────────┐      └───────────────┘
│  │           check           │
│  └─────────────┬─────────────┘
│  ┌─────────────┴─────────────┐
└──┤      close callbacks      │
   └───────────────────────────┘
```

*note: each box will be referred to as a "phase" of the event loop.*

![image.png](https://i.loli.net/2019/11/17/7EBTpXbawfNJsYl.png)

#### Nodejs has 5 major phases.



1) timers phase.
2) pending call back phase.
3) poll phase
4) check (set immediate).
5) close

- **timers**: this phase executes callbacks scheduled by `setTimeout()` and `setInterval()`.
- **pending callbacks**: executes I/O callbacks deferred to the next loop iteration.
- **idle, prepare**: only used internally.
- **poll**: retrieve new I/O events; execute I/O related callbacks (almost all with the exception of close callbacks, the ones scheduled by timers, and `setImmediate()`); node will block here when appropriate.
- **check**: `setImmediate()` callbacks are invoked here.
- **close callbacks**: some close callbacks, e.g. `socket.on('close', ...)`.

Between each run of the event loop, Node.js checks if it is waiting for any asynchronous I/O or timers and shuts down cleanly if there are not any.