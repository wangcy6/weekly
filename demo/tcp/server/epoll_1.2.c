//
// Created by leo on 2017/4/29.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAXEVENTS 64
#define MAXSIZE 1024


static int make_socket_non_blocking (int sfd)
{
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }

    return 0;
}


static int create_and_bind (char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;     // 支持 IPv4 和 IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_flags = AI_PASSIVE;     // 监听套接字

    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0)
    {
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
        {
            // 已成功绑定套接字
            break;
        }

        close (sfd);
    }

    if (rp == NULL)
    {
        fprintf (stderr, "Could not bind\n");
        return -1;
    }

    freeaddrinfo (result);

    return sfd;
}

//gcc epoll_1.c -o epollServer
int main (int argc, char *argv[])
{
    int sfd, s;
    int efd;
    
    struct epoll_event event; // 事件
    struct epoll_event *events; //激活事件集合

    char buffer[MAXSIZE];
    if (argc != 2)
    {
        fprintf (stderr, "Usage: %s [port]\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    sfd = create_and_bind (argv[1]);
    if (sfd == -1)
        abort ();

    s = make_socket_non_blocking (sfd);
    if (s == -1)
        abort ();

    s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }

    efd = epoll_create1 (0);
    if (efd == -1)
    {
        perror ("epoll_create");
        abort ();
    }

    event.data.fd = sfd;
    // ET 模式
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);
    if (s == -1)
    {
        perror ("epoll_ctl");
        abort ();
    }

    // 用来存储epoll_wait返回的就绪文件描述符列表
    events = calloc (MAXEVENTS, sizeof event);

    // 主循环
    while (1)
    {
        int n, i;
       
        n = epoll_wait (efd, events, MAXEVENTS, -1);
        printf("wake up process n=%d .... \n",n);



        for (i = 0; i < n; i++)
        {
            if(events[i].data.fd < 0)
            {        
                    printf("fd is < 0 \n");
                    continue;
            }
            else if (sfd == events[i].data.fd)
            {
                //监听套接字就绪，表明有一个或者多个连接进来
                while (1)
                {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                    in_len = sizeof in_addr;
                    infd = accept (sfd, &in_addr, &in_len);
                    if (infd == -1)
                    {
                        if ((errno == EAGAIN) ||
                            (errno == EWOULDBLOCK))
                        {
                            // 处理完所有的连接
                            break;
                        }
                        else
                        {
                            perror ("accept");
                            break;
                        }
                    }

                    s = getnameinfo (&in_addr, in_len,
                                     hbuf, sizeof hbuf,
                                     sbuf, sizeof sbuf,
                                     NI_NUMERICHOST | NI_NUMERICSERV);
                    if (s == 0)
                    {
                        printf("Accepted connection on descriptor %d "
                                       "(host=%s, port=%s)\n", infd, hbuf, sbuf);
                    }

                    // 设置已连接套接字为非阻塞，并且加入到 epoll 实例监测中
                    s = make_socket_non_blocking (infd);
                    if (s == -1)
                        abort ();

                    event.data.fd = infd;
                    // ET 模式
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1)
                    {
                        perror ("epoll_ctl");
                        abort ();
                    }
                }
                continue;
            }
            else
            {     
                if(events[i].events & EPOLLIN)
                {
                    //如果是已经连接的用户，并且收到数据，
                    //那么进行读入
                    //https://baike.baidu.com/item/epoll

                     int sockfd_r =events[i].data.fd;
                     memset(buffer, 0, sizeof(buffer));
                    //printf("sockfd_r=%d read data begin ...\n",sockfd_r);
                    //////////////////////step 01 socket读取数据逻辑///////////////////////
                    while (1)
                    {    

                        
                        ssize_t  count = read (sockfd_r, buffer, sizeof(buffer));
                        printf("read count=%d, buf =%s \n",count,buffer);

                        if (count == -1)
                        {
                            // 如果 errno == EAGAIN，说明所有数据已读取完毕
                            // 如果 errno != EAGAIN，说明读取出错
                            if (errno != EAGAIN)
                            {
                            // 读取出错
                            perror ("read");
                            
                            }
                           // printf("buffer is empty errno=EAGAIN \n");
                            break;
                        }
                        else if (count == 0)
                        {
                            // 客户端断开了连接
                            // printf(" client peer is closed,  s \n");
                             close (sockfd_r);
                          
                            break;
                        }

                    }  
                      //printf("sockfd_r=%d read data end ...\n",sockfd_r);
                    /////////////////step 02 修改sockfd_r上要处理的事件为EPOLLOUT//////////////////
                    event.data.fd = sockfd_r;
                    event.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &event);

        
                }else if(events[i].events & EPOLLOUT)
               {      //自己i写成n了，不存在的链接，根本代码执行不到这里，copy错误
                    //如果有数据发送

                    //printf("........send begin.EPOLLOUT .... \n");

                   int sockfd_w = events[i].data.fd; //自己i写成n了，一个不存在的链接肯定发送失败。你真2,都是copy造成的错误
                    
                   while(1)
                   {
                       int len=write(sockfd_w, buffer, sizeof(buffer));
                   
                        printf("fd=%d,write=%d data=%s\n",sockfd_w,len,buffer);
                   }
                   


            

               }
               
        }
     }
    } //end main loop 3490

    free (events);

    close (sfd);

    return EXIT_SUCCESS;
}
//./epollServer 3490