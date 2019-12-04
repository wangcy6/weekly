#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/**
1. 理论
https://unix.stackexchange.com/questions/16455/interruption-of-system-calls-when-a-signal-is-caught


http://www.delorie.com/djgpp/doc/ug/interrupts/inthandlers1.html
in order to differentiate between signals and software interrupts,
we'll consider that :
 - Software interrupts - Are explicitly triggered with an INT instruction and
are therefore synchronous, as discussed previously.
 - Signals - Don't make use of the INT instruction and usually occur
asynchronously, that is, the process doesn't know ahead of time exactly when a
signal will make its appearance. Signals can be generated synchronously or
asynchronously (the latter being more common).
   
generate synchronous signals(系统内部产生)
   
Signals can be generated synchronously or asynchronously (the latter being more
common). If you try to reference an unmapped, protected or bad memory address a
SIGSEV or SIGBUS can be issued, a floating point exception can generate a
SIGFPE, and the execution of an illegal instruction can generate SIGILL. All the
previous events, called errors if you recall, generate synchronous signals.


asynchronously:

   Events such as keyboard interrupts generate signals (SIGINT) which are sent
to the target process. Such events generate asynchronous signals. Signals are
software interrupts. Most nontrivial application programs need to deal with
   signals. Signals provide a way of handling asynchronous events
   
   Signals are classic examples of asynchronous events. They occur at what
appear to be random times to the process.

https://docs.oracle.com/cd/E19683-01/806-6867/gen-15/index.html Synchronous
Signals

Because such a synchronous signal usually means that something is seriously
wrong with the whole process, and not just with a thread, terminating the
process is often a good choice.
Asynchronous Signals
https://docs.oracle.com/cd/E19683-01/806-6867/gen-16/index.html

https://stackoverflow.com/questions/4959524/when-to-check-for-eintr-and-repeat-the-function-call
产生（同步，异步）
投递（系统调用完成返回，中断返回，保存现场返回 处理信号）
处理（1 忽视 2 默认 3 自定义）
2. 测试理论

**/

int main(void) { return 0; }