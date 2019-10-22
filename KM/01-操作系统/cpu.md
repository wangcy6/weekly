# 小王提问

- 线程函数入口是什么





# 知识卡

## rocess vs Thread – Difference between Process and Thread

| **Process**                                                  | **Thread**                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1) System calls involved in process.                         | 1) No system calls involved.                                 |
| 2) Context switching required.                               | 2) No context switching required.                            |
| 3) Different process have different copies of code and data. | 3) Sharing same copy of code and data can be possible among different threads.. |
| 4) Operating system treats different process differently.    | 4) All user level threads treated as single task for operating system. |
| 5) If a process got blocked, remaining process continue their work. | 5) If a user level thread got blocked, all other threads get blocked since they are treated as single task to OS. (Noted: This is can be avoided in kernel level threads). |
| 6) Processes are independent.                                | 6) Threads exist as subsets of a process. They are dependent. |
| 7) Process run in separate memory space.                     | 7) Threads run in shared memory space. And use memory of process which it belong to. |
| 8) Processes have their own program counter (PC), register set, and stack space. | 8) Threads share Code section, data section, Address space with other threads. |
| 9) Communication between processes requires some time.       | 9) Communication between processes requires less time than processes. |
| 10) Processes don’t share the memory with any other process. | 10) Threads share the memory with other threads of the same process |
| 11) Process have overhead.                                   | 11) Threads have no overhead.                                |

 https://stackoverflow.com/questions/200469/what-is-the-difference-between-a-process-and-a-thread 

# 动手实验

### 创建一个线程 

 / proc/PID/task来看该程序有多少线程在运行： 

 /proc/PID/maps就是进程的地址空间 



~~~c
[root@vm-10-115-37-45 study]# pstack 17846
Thread 4 (Thread 0x7f302307f700 (LWP 17851)):
#0  0x00007f302313e66d in nanosleep () from /lib64/libc.so.6
#1  0x00007f302313e504 in sleep () from /lib64/libc.so.6
#2  0x00000000004009b2 in say_hello(void*) ()
#3  0x00007f3023c69dc5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f302317776d in clone () from /lib64/libc.so.6
Thread 3 (Thread 0x7f302287e700 (LWP 17852)):
#0  0x00007f302313e66d in nanosleep () from /lib64/libc.so.6
#1  0x00007f302313e504 in sleep () from /lib64/libc.so.6
#2  0x00000000004009b2 in say_hello(void*) ()
#3  0x00007f3023c69dc5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f302317776d in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7f302207d700 (LWP 17853)):
#0  0x00007f302313e66d in nanosleep () from /lib64/libc.so.6
#1  0x00007f302313e504 in sleep () from /lib64/libc.so.6
#2  0x00000000004009b2 in say_hello(void*) ()
#3  0x00007f3023c69dc5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f302317776d in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7f302408b740 (LWP 17846)):
#0  0x00007f302313e66d in nanosleep () from /lib64/libc.so.6
#1  0x00007f302313e504 in sleep () from /lib64/libc.so.6
#2  0x0000000000400a38 in main ()
~~~





