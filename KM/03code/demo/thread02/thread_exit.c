#include <stdio.h>
#include <pthread.h>
// https://www.fengbohello.top/archives/linux-pthread-lifecycle
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

  //注意，这里执行了 return
  return NULL;

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