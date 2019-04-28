#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/epoll.h>  
#include <netdb.h>  
#include <string.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <sys/wait.h>  
#define PROCESS_NUM 10  
static int  create_and_bind (char *port)  
{  
    int fd = socket(PF_INET, SOCK_STREAM, 0);  
    struct sockaddr_in serveraddr;  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    serveraddr.sin_port = htons(atoi(port));  
    bind(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));  
    return fd;  
}  
static int  make_socket_non_blocking (int sfd)  
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
  
#define MAXEVENTS 64  
 
int main (int argc, char *argv[])  
{  
    int sfd, s;  
    int efd;  
    struct epoll_event event;  
    struct epoll_event *events;  
 
    sfd = create_and_bind("1234");  
    if (sfd == -1)  
        abort ();  
 
    s = make_socket_non_blocking (sfd);  
    if (s == -1)  
        abort ();  
 
    s = listen(sfd, SOMAXCONN);  
    if (s == -1)  
    {  
        perror ("listen");  
        abort ();  
    }  
 
    efd = epoll_create(MAXEVENTS);  
    if (efd == -1)  
    {  
        perror("epoll_create");  
        abort();  
    }  
 
    event.data.fd = sfd;  
    //event.events = EPOLLIN | EPOLLET;  
    event.events = EPOLLIN;  
    s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);  
    if (s == -1)  
    {  
        perror("epoll_ctl");  
        abort();  
    }  
 
    /* Buffer where events are returned */  
    events = calloc(MAXEVENTS, sizeof event); 
	
    int k=0;  
    for(k = 0; k < PROCESS_NUM; k++)  
    {  
        int pid = fork();  
        if(pid == 0)  
        {  
            /* child The event loop */  
            while (1)  
            {  
                int n, i;  
                n = epoll_wait(efd, events, MAXEVENTS, -1);  
                printf("process %d return from epoll_wait!\n", getpid());  
	            /* sleep here is very important!*/  
                //sleep(2);  
	            for (i = 0; i < n; i++)  
                {  
                    if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))  
                    {  
                        /* An error has occured on this fd, or the socket is not  
                        ready for reading (why were we notified then?) */  
                        fprintf (stderr, "epoll error\n");  
                        close (events[i].data.fd);  
                        continue;  
                    }
                    //connect 					
                    else if (sfd == events[i].data.fd)  
                    {  
                        /* We have a notification on the listening socket, which  
                        means one or more incoming connections. */  
                        struct sockaddr in_addr;  
                        socklen_t in_len;  
                        int infd;  
                        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];  
 
                        in_len = sizeof in_addr;  
                        infd = accept(sfd, &in_addr, &in_len);  
                        if (infd == -1)  
                        {  
                            printf("process %d accept failed!\n", getpid());  
                            break;  
                        }  
                        printf("process %d accept successed!\n", getpid());  
 
                        /* Make the incoming socket non-blocking and add it to the  
                        list of fds to monitor. */  
                        close(infd); 
                    }  
                }  
            }  
        }  
    }  
    int status;  
    wait(&status);  
    free (events);  
    close (sfd);  
    return EXIT_SUCCESS;  
}  