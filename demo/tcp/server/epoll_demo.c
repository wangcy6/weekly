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


int main (int argc, char *argv[])
{
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;

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
        for (i = 0; i < n; i++)
        {
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN)))
            {
                // 监测的文件描述符出错了
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
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
                // 已连接套接字可读，我们读取该套接字所有的数据并打印出来
                // 由于使用了 ET 模式，我们必须将所有可读数据读取完毕
                int done = 0;

                while (1)
                {
                    ssize_t count;
                    char buf[512];

                    count = read (events[i].data.fd, buf, sizeof buf);
                    if (count == -1)
                    {
                        // 如果 errno == EAGAIN，说明所有数据已读取完毕
                        // 如果 errno != EAGAIN，说明读取出错
                        if (errno != EAGAIN)
                        {
                            // 读取出错
                            perror ("read");
                            done = 1;
                        }
                        break;
                    }
                    else if (count == 0)
                    {
                        // 客户端断开了连接
                        done = 1;
                        break;
                    }

                    // 打印到标准输出
                    s = write (1, buf, count);
                    if (s == -1)
                    {
                        perror ("write");
                        abort ();
                    }
                }

                if (done)
                {
                    printf ("Closed connection on descriptor %d\n",
                            events[i].data.fd);

                    // 关闭连接
                    close (events[i].data.fd);
                }
            }
        }
    }

    free (events);

    close (sfd);

    return EXIT_SUCCESS;
}
