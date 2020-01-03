# gdb调试步骤

## 发现错误  crashes



 [crashes](https://en.wikipedia.org/wiki/Crash_(computing)): 进程**退出**了

- [What does Crash mean](https://www.techopedia.com/definition/13399/crash) or [What is a Crash](https://www.techopedia.com/definition/13399/crash)

> 我听到crash这个单词时候，
>
> 我回忆10秒，根本不知道什么意思，
>
> 在我回忆10秒，根本不知道什么意思，
>
> 在我回忆10秒，根本不知道什么意思， 怎办？
>
> 我以前听到进程 core了。
>
> crash ！=core
>
> 虽然我不是这样想，最后通过对话，发现自己就是这样做的！
>
> 
>
> 这个属于想当然，一个严重的错误思维，不问具体情况，按照自己感觉去理解
>
> 这个属于想当然，一个严重的错误思维，不问具体情况，按照自己感觉去理解
>
> crash ==core



没有core问题

- echo $? 139  
- dmesg 
- /var/*log*/*messages*







### 连结



gdb attach process-id /gdb -p xx

gdb ./aut  core.

gdb ./a.out



- 设置源文件查找路径 gdb  a.out -d /search/code/some [生产环境]

- GDB如何调试没有符号表(未加-g选项的编译)的程序

  list
  No symbol table is loaded.  Use the "file" command.
  
  

### 设置断点



b read_write_lock.c:51



> fuck 没有不是-g选项，无法设置断点
>
> Missing separate debuginfos, use: debuginfo-install glibc-2.17-157.el7_3.2.x86_64

### 运行

 directory  path

set args 1

[show args](https://sourceware.org/gdb/onlinedocs/gdb/Arguments.html#Arguments)

r

### 调试

线程：

```shell
info threads
thread thread-id

set scheduler-locking on //锁定一个线程
thread apply all bt //执行命令 
//thread apply [thread-id-list | all [-ascending]] [flag]… command

 set print thread-events off //which controls printing of messages on thread start and exit.
```



进程：

```
set follow-fork-mode child
```

### 打印变量 ！！

```scala
set print object on 
//When displaying a pointer to an object, identify the actual (derived) type of the object rather than the declared type, using the virtual function table


whatis p
ptype p

set print pretty on
```



- 打印STL容器中的内容

- 打印数组

  ```
  set print elements unlimited
  p *array@len
  p/x (short[2])0x12345678
   
  info proc mapping
   p 'static-1.c'::var
  ```







### 改变程序的执行！！

### 插件

- ~/.gdbinit 

- gdbgui https://www.gdbgui.com/

  

### 汇编！！

# disassemble main 





看堆栈，检查寄存器，下断点，逐步排查，看源码。



### ref



https://wizardforcel.gitbooks.io/100-gdb-tips/set-scheduler-locking-on.html

https://sourceware.org/gdb/onlinedocs/gdb/index.html#SEC_Contents

http://llxwj.top/post/linux/gdb-debugging-guide-to-the-high-quality-guide-written-by-master/

