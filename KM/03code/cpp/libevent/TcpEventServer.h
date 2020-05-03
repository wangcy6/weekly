//TcpEventServer.h
#ifndef TCPEVENTSERVER_H_
#define TCPEVENTSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>

#include <map>
using std::map;

#include <event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

class TcpEventServer;
class Conn;
class ConnQueue;
struct LibeventThread;

//这个类一个链表的结点类，结点里存储各个连接的信息，
//并提供了读写数据的接口
class Conn
{
  //此类只能由TcpBaseServer创建，
  //并由ConnQueue类管理
  friend class ConnQueue;
  friend class TcpEventServer;

private:
  const int m_fd;				//socket的ID
  evbuffer *m_ReadBuf;		//读数据的缓冲区
  evbuffer *m_WriteBuf;		//写数据的缓冲区

  Conn *m_Prev;				//前一个结点的指针
  Conn *m_Next;				//后一个结点的指针
  LibeventThread *m_Thread;

  Conn(int fd=0);
  ~Conn();

public:
  LibeventThread *GetThread() { return m_Thread; }
  int GetFd() { return m_fd; }

  //获取可读数据的长度
  int GetReadBufferLen()
  { return evbuffer_get_length(m_ReadBuf); }

  //从读缓冲区中取出len个字节的数据，存入buffer中，若不够，则读出所有数据
  //返回读出数据的字节数
  int GetReadBuffer(char *buffer, int len)
  { return evbuffer_remove(m_ReadBuf, buffer, len); }

  //从读缓冲区中复制出len个字节的数据，存入buffer中，若不够，则复制出所有数据
  //返回复制出数据的字节数
  //执行该操作后，数据还会留在缓冲区中，buffer中的数据只是原数据的副本
  int CopyReadBuffer(char *buffer, int len)
  { return evbuffer_copyout(m_ReadBuf, buffer, len); }

  //获取可写数据的长度
  int GetWriteBufferLen()
  { return evbuffer_get_length(m_WriteBuf); }

  //将数据加入写缓冲区，准备发送
  int AddToWriteBuffer(char *buffer, int len)
  { return evbuffer_add(m_WriteBuf, buffer, len); }

  //将读缓冲区中的数据移动到写缓冲区
  void MoveBufferData()
  { evbuffer_add_buffer(m_WriteBuf, m_ReadBuf); }

};

//带头尾结点的双链表类，每个结点存储一个连接的数据
class ConnQueue
{
private:
  Conn *m_head;
  Conn *m_tail;
public:
  ConnQueue();
  ~ConnQueue();
  Conn *InsertConn(int fd, LibeventThread *t);
  void DeleteConn(Conn *c);
  //void PrintQueue();
};

//每个子线程的线程信息
struct LibeventThread
{
  pthread_t tid;				//线程的ID
  struct event_base *base;	//libevent的事件处理机
  struct event notifyEvent;	//监听管理的事件机
  int notifyReceiveFd;		//管理的接收端
  int notifySendFd;			//管道的发送端
  ConnQueue connectQueue;		//socket连接的链表

  //在libevent的事件处理中要用到很多回调函数，不能使用类隐含的this指针
  //所以用这样方式将TcpBaseServer的类指针传过去
  TcpEventServer *tcpConnect;	 //TcpBaseServer类的指针
};

class TcpEventServer
{
private:
  int m_ThreadCount;					//子线程数
  int m_Port;							//监听的端口
  LibeventThread *m_MainBase;			//主线程的libevent事件处理机
  LibeventThread *m_Threads;			//存储各个子线程信息的数组
  map<int, event*> m_SignalEvents;	//自定义的信号处理

public:
  static const int EXIT_CODE = -1;

private:
  //初始化子线程的数据
  void SetupThread(LibeventThread *thread);

  //子线程的入门函数
  static void *WorkerLibevent(void *arg);
  //（主线程收到请求后），对应子线程的处理函数
  static void ThreadProcess(int fd, short which, void *arg);
  //被libevent回调的各个静态函数
  static void ListenerEventCb(evconnlistener *listener, evutil_socket_t fd,
    sockaddr *sa, int socklen, void *user_data);
  static void ReadEventCb(struct bufferevent *bev, void *data);
  static void WriteEventCb(struct bufferevent *bev, void *data); 
  static void CloseEventCb(struct bufferevent *bev, short events, void *data);

protected:
  //这五个虚函数，一般是要被子类继承，并在其中处理具体业务的

  //新建连接成功后，会调用该函数
  virtual void ConnectionEvent(Conn *conn) { }

  //读取完数据后，会调用该函数
  virtual void ReadEvent(Conn *conn) { }

  //发送完成功后，会调用该函数（因为串包的问题，所以并不是每次发送完数据都会被调用）
  virtual void WriteEvent(Conn *conn) { }

  //断开连接（客户自动断开或异常断开）后，会调用该函数
  virtual void CloseEvent(Conn *conn, short events) { }

  //发生致命错误（如果创建子线程失败等）后，会调用该函数
  //该函数的默认操作是输出错误提示，终止程序
  virtual void ErrorQuit(const char *str);

public:
  TcpEventServer(int count);
  ~TcpEventServer();

  //设置监听的端口号，如果不需要监听，请将其设置为EXIT_CODE
  void SetPort(int port)
  { m_Port = port; }

  //开始事件循环
  bool StartRun();
  //在tv时间里结束事件循环
  //否tv为空，则立即停止
  void StopRun(timeval *tv);

  //添加和删除信号处理事件
  //sig是信号，ptr为要回调的函数
  bool AddSignalEvent(int sig, void (*ptr)(int, short, void*));
  bool DeleteSignalEvent(int sig);

  //添加和删除定时事件
  //ptr为要回调的函数，tv是间隔时间，once决定是否只执行一次
  event *AddTimerEvent(void(*ptr)(int, short, void*),
    timeval tv, bool once);
  bool DeleteTImerEvent(event *ev);
};

#endif

实现文件：TcpEventServer.cpp

//TcpEventServer.cpp
#include "TcpEventServer.h"

Conn::Conn(int fd) : m_fd(fd)
{
  m_Prev = NULL;
  m_Next = NULL;
}

Conn::~Conn()
{

}

ConnQueue::ConnQueue()
{
  //建立头尾结点，并调整其指针
  m_head = new Conn(0);
  m_tail = new Conn(0);
  m_head->m_Prev = m_tail->m_Next = NULL;
  m_head->m_Next = m_tail;
  m_tail->m_Prev = m_head;
}

ConnQueue::~ConnQueue()
{
  Conn *tcur, *tnext;
  tcur = m_head;
  //循环删除链表中的各个结点
  while( tcur != NULL )
  {
    tnext = tcur->m_Next;
    delete tcur;
    tcur = tnext;
  }
}

Conn *ConnQueue::InsertConn(int fd, LibeventThread *t)
{
  Conn *c = new Conn(fd);
  c->m_Thread = t;
  Conn *next = m_head->m_Next;

  c->m_Prev = m_head;
  c->m_Next = m_head->m_Next;
  m_head->m_Next = c;
  next->m_Prev = c;
  return c;
}

void ConnQueue::DeleteConn(Conn *c)
{
  c->m_Prev->m_Next = c->m_Next;
  c->m_Next->m_Prev = c->m_Prev;
  delete c;
}

/*
void ConnQueue::PrintQueue()
{
 Conn *cur = m_head->m_Next;
 while( cur->m_Next != NULL )
 {
  printf("%d ", cur->m_fd);
  cur = cur->m_Next;
 }
 printf("\n");
}
*/

TcpEventServer::TcpEventServer(int count)
{
  //初始化各项数据
  m_ThreadCount = count;
  m_Port = -1;
  m_MainBase = new LibeventThread;
  m_Threads = new LibeventThread[m_ThreadCount];
  m_MainBase->tid = pthread_self();
  m_MainBase->base = event_base_new();

  //初始化各个子线程的结构体
  for(int i=0; i<m_ThreadCount; i++)
  {
    SetupThread(&m_Threads[i]);
  }

}

TcpEventServer::~TcpEventServer()
{
  //停止事件循环（如果事件循环没开始，则没效果）
  StopRun(NULL);

  //释放内存
  event_base_free(m_MainBase->base);
  for(int i=0; i<m_ThreadCount; i++)
    event_base_free(m_Threads[i].base);

  delete m_MainBase;
  delete [] m_Threads;
}

void TcpEventServer::ErrorQuit(const char *str)
{
  //输出错误信息，退出程序
  fprintf(stderr, "%s", str);   
  if( errno != 0 )    
    fprintf(stderr, " : %s", strerror(errno));    
  fprintf(stderr, "\n");        
  exit(1);    
}

void TcpEventServer::SetupThread(LibeventThread *me)
{
  //建立libevent事件处理机制
  me->tcpConnect = this;
  me->base = event_base_new();
  if( NULL == me->base )
    ErrorQuit("event base new error");

  //在主线程和子线程之间建立管道
  int fds[2];
  if( pipe(fds) )
    ErrorQuit("create pipe error");
  me->notifyReceiveFd = fds[0];
  me->notifySendFd = fds[1];

  //让子线程的状态机监听管道
  event_set( &me->notifyEvent, me->notifyReceiveFd,
    EV_READ | EV_PERSIST, ThreadProcess, me );
  event_base_set(me->base, &me->notifyEvent);
  if ( event_add(&me->notifyEvent, 0) == -1 )
    ErrorQuit("Can't monitor libevent notify pipe\n");
}

void *TcpEventServer::WorkerLibevent(void *arg)
{
  //开启libevent的事件循环，准备处理业务
  LibeventThread *me = (LibeventThread*)arg;
  //printf("thread %u started\n", (unsigned int)me->tid);
  event_base_dispatch(me->base);
  //printf("subthread done\n");
}

bool TcpEventServer::StartRun()
{
  evconnlistener *listener;

  //如果端口号不是EXIT_CODE，就监听该端口号
  if( m_Port != EXIT_CODE )
  {
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_Port);
    listener = evconnlistener_new_bind(m_MainBase->base, 
      ListenerEventCb, (void*)this,
      LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
      (sockaddr*)&sin, sizeof(sockaddr_in));
    if( NULL == listener )
      ErrorQuit("TCP listen error");
  }

  //开启各个子线程
  for(int i=0; i<m_ThreadCount; i++)
  {
    pthread_create(&m_Threads[i].tid, NULL,  
      WorkerLibevent, (void*)&m_Threads[i]);
  }

  //开启主线程的事件循环
  event_base_dispatch(m_MainBase->base);

  //事件循环结果，释放监听者的内存
  if( m_Port != EXIT_CODE )
  {
    //printf("free listen\n");
    evconnlistener_free(listener);
  }
}

void TcpEventServer::StopRun(timeval *tv)
{
  int contant = EXIT_CODE;
  //向各个子线程的管理中写入EXIT_CODE，通知它们退出
  for(int i=0; i<m_ThreadCount; i++)
  {
    write(m_Threads[i].notifySendFd, &contant, sizeof(int));
  }
  //结果主线程的事件循环
  event_base_loopexit(m_MainBase->base, tv);
}

void TcpEventServer::ListenerEventCb(struct evconnlistener *listener, 
                  evutil_socket_t fd,
                  struct sockaddr *sa, 
                  int socklen, 
                  void *user_data)
{
  TcpEventServer *server = (TcpEventServer*)user_data;

  //随机选择一个子线程，通过管道向其传递socket描述符
  int num = rand() % server->m_ThreadCount;
  int sendfd = server->m_Threads[num].notifySendFd;
  write(sendfd, &fd, sizeof(evutil_socket_t));
}

void TcpEventServer::ThreadProcess(int fd, short which, void *arg)
{
  LibeventThread *me = (LibeventThread*)arg;

  //从管道中读取数据（socket的描述符或操作码）
  int pipefd = me->notifyReceiveFd;
  evutil_socket_t confd;
  read(pipefd, &confd, sizeof(evutil_socket_t));

  //如果操作码是EXIT_CODE，则终于事件循环
  if( EXIT_CODE == confd )
  {
    event_base_loopbreak(me->base);
    return;
  }

  //新建连接
  struct bufferevent *bev;
  bev = bufferevent_socket_new(me->base, confd, BEV_OPT_CLOSE_ON_FREE);
  if (!bev)
  {
    fprintf(stderr, "Error constructing bufferevent!");
    event_base_loopbreak(me->base);
    return;
  }

  //将该链接放入队列
  Conn *conn = me->connectQueue.InsertConn(confd, me);

  //准备从socket中读写数据
  bufferevent_setcb(bev, ReadEventCb, WriteEventCb, CloseEventCb, conn);
  bufferevent_enable(bev, EV_WRITE);
  bufferevent_enable(bev, EV_READ);

  //调用用户自定义的连接事件处理函数
  me->tcpConnect->ConnectionEvent(conn);
}

void TcpEventServer::ReadEventCb(struct bufferevent *bev, void *data)
{
  Conn *conn = (Conn*)data;
  conn->m_ReadBuf = bufferevent_get_input(bev);
  conn->m_WriteBuf = bufferevent_get_output(bev);

  //调用用户自定义的读取事件处理函数
  conn->m_Thread->tcpConnect->ReadEvent(conn);
} 

void TcpEventServer::WriteEventCb(struct bufferevent *bev, void *data)
{
  Conn *conn = (Conn*)data;
  conn->m_ReadBuf = bufferevent_get_input(bev);
  conn->m_WriteBuf = bufferevent_get_output(bev);

  //调用用户自定义的写入事件处理函数
  conn->m_Thread->tcpConnect->WriteEvent(conn);

}

void TcpEventServer::CloseEventCb(struct bufferevent *bev, short events, void *data)
{
  Conn *conn = (Conn*)data;
  //调用用户自定义的断开事件处理函数
  conn->m_Thread->tcpConnect->CloseEvent(conn, events);
  conn->GetThread()->connectQueue.DeleteConn(conn);
  bufferevent_free(bev);
}

bool TcpEventServer::AddSignalEvent(int sig, void (*ptr)(int, short, void*))
{
  //新建一个信号事件
  event *ev = evsignal_new(m_MainBase->base, sig, ptr, (void*)this);
  if ( !ev || 
    event_add(ev, NULL) < 0 )
  {
    event_del(ev);
    return false;
  }

  //删除旧的信号事件（同一个信号只能有一个信号事件）
  DeleteSignalEvent(sig);
  m_SignalEvents[sig] = ev;

  return true;
}

bool TcpEventServer::DeleteSignalEvent(int sig)
{
  map<int, event*>::iterator iter = m_SignalEvents.find(sig);
  if( iter == m_SignalEvents.end() )
    return false;

  event_del(iter->second);
  m_SignalEvents.erase(iter);
  return true;
}

event *TcpEventServer::AddTimerEvent(void (*ptr)(int, short, void *), 
                  timeval tv, bool once)
{
  int flag = 0;
  if( !once )
    flag = EV_PERSIST;

  //新建定时器信号事件
  event *ev = new event;
  event_assign(ev, m_MainBase->base, -1, flag, ptr, (void*)this);
  if( event_add(ev, &tv) < 0 )
  {
    event_del(ev);
    return NULL;
  }
  return ev;
}

bool TcpEventServer::DeleteTImerEvent(event *ev)
{
  int res = event_del(ev);
  return (0 == res);
}