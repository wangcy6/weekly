// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#include "Thread.h"

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace CurrentThread
{
  __thread const char* t_threadName = "unknown";
}
}

namespace
{
__thread pid_t t_cachedTid = 0;

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
  t_cachedTid = gettid();
  muduo::CurrentThread::t_threadName = "main";
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer
{
 public:
  ThreadNameInitializer()
  {
    muduo::CurrentThread::t_threadName = "main";
    pthread_atfork(NULL, NULL, &afterFork);
  }
};

ThreadNameInitializer init;
}

using namespace muduo;

pid_t CurrentThread::tid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = gettid();
  }
  return t_cachedTid;
}

const char* CurrentThread::name()
{
  return t_threadName;
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const std::string& n)
  : started_(false),
    pthreadId_(0),
    tid_(0),
    func_(func),
    name_(n)
{
  numCreated_.increment();
}

Thread::~Thread()
{
}

void Thread::start()
{
  assert(!started_);
  started_ = true;
  pthread_create(&pthreadId_, NULL, &startThread, this);
}

void Thread::join()
{
  assert(started_);
  pthread_join(pthreadId_, NULL);
}

void* Thread::startThread(void* obj)
{
  Thread* thread = static_cast<Thread*>(obj);
  thread->runInThread();
  return NULL;
}

void Thread::runInThread()
{
  tid_ = CurrentThread::tid();
  muduo::CurrentThread::t_threadName = name_.c_str();
  func_();
  muduo::CurrentThread::t_threadName = "finished";
}

