#include <stdio.h>
#include <pthread.h>
// https://www.fengbohello.top/archives/linux-pthread-lifecycle
/**
   man pthread_create
   See pthread_self(3) for further information on the thread ID returned in
   *thread by pthread_create().  Unless real-time scheduling policies are being
   employed, after a call to pthread_create(), it is indeterminate which
   thread—the caller or the new thread—will next execute.

       A thread may either be joinable or detached.
           If a thread is joinable, then another thread can call pthread_join(3)
   to wait for the thread to terminate and fetch its exit sta‐ tus. Only  when a
   terminated joinable thread has been joined are the last of its resources
   released back to the system.

           When a detached thread terminates, its resources are
       automatically released back to the system: it is not possible to join
   with the thread in order to obtain its exit status. Making a thread detached
   is useful for some types of daemon  threads  whose  exit  status  the
   application does not need to care about. By default, a new thread is created
   in a joinable state, unless attr was set to create the thread in a detached
   state (using pthread_attr_setdetachstate(3)).
           
            pthread_exit - terminate calling thread
                DESCRIPTION
       The  pthread_exit()  function  terminates the calling thread and returns
   a value via retval that (if the thread is joinable) is available to another
   thread in the same process that calls pthread_join(3).(通知)

       Any clean-up handlers established by pthread_cleanup_push(3) that have
   not yet been popped, are popped (in the reverse of the order in which they
   were  pushed)  and  executed. If the thread has any thread-specific data,
   then, after the clean-up handlers have been executed, the corresponding
   destructor functions are called, in an unspecified
   order.（pthread_cleanup_push注册回调发送）

       When  a  thread  terminates,  process-shared  resources (e.g., mutexes,
   condition variables, semaphores, and file descriptors) are not released, and
   functions registered using atexit(3) are not called. （atexit注册回调不发生）

       After the last thread in a process terminates, the process terminates as
   by calling exit(3) with an exit status of zero; thus, process-shared
   resources are released and  func‐ tions registered using atexit(3) are
   called. （atexit注册回调发送进程退出） valgrind --leak-check=full
   --show-reachable=yes ./a.out

*/
void handlers(void *arg) {
  if (NULL != arg) {
    printf("%s() : [%s]\n", __func__, (char *)arg);
  } else {
    printf("%s()\n", __func__);
  }
}

void *thread_start(void *arg) {
  printf("hello, this is thrad [%u]\n", (unsigned int)pthread_self());
  pthread_cleanup_push(handlers, "one");
  pthread_cleanup_push(handlers, "two");
  pthread_cleanup_push(handlers, "three");

  //注意，这里执行了 pthread_exit() 函数
  pthread_exit("he~he~");

  pthread_cleanup_pop(1);
  pthread_cleanup_pop(2);
  pthread_cleanup_pop(3);

  return NULL;
}

int main() {
  pthread_t pt;
  int errn = pthread_create(&pt, NULL, thread_start, NULL);

  if (0 != errn) {
    printf("error [%d], when create pthread\n", errn);
    return -1;
  } else {
    printf("create thread success, threadid : [%u]\n", (unsigned int)pt);
  }
  void *r = NULL;
  errn = pthread_join(pt, &r);
  if (0 != errn) {
    printf("error happend when join, errno = [%d]\n", errn);
    return -1;
  } else {
    printf("thread [%u] over\n", (unsigned int)pt);
  }
  if (NULL != r) {
    printf("thread return : [%s]\n", (const char *)r);
  }

  return 0;
}