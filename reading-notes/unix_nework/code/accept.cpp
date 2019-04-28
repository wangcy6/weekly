#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <assert.h>  
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#define IP   "127.0.0.1"
#define PORT  8888
#define WORKER 4
int worker(int listenfd, int i)
{
    while (1) {
        printf("I am worker %d, begin to accept connection.\n", i);
        struct sockaddr_in client_addr;  
        socklen_t client_addrlen = sizeof( client_addr );  
        int connfd = accept( listenfd, ( struct sockaddr* )&client_addr, &client_addrlen );  
        if (connfd != -1) {
            printf("worker %d accept a connection success.\t", i);
            printf("ip :%s\t",inet_ntoa(client_addr.sin_addr));
            printf("port: %d \n",client_addr.sin_port);
        } else {
            printf("worker %d accept a connection failed,error:%s", i, strerror(errno));
			close(connfd);
        }
    }
    return 0;
}
int main()
{
    int i = 0;
    struct sockaddr_in address;  
    bzero(&address, sizeof(address));  
    address.sin_family = AF_INET;  
    inet_pton( AF_INET, IP, &address.sin_addr);  
    address.sin_port = htons(PORT);  
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);  
    assert(listenfd >= 0);  
    int ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));  
    assert(ret != -1);  
    ret = listen(listenfd, 5);  
    assert(ret != -1);  
    for (i = 0; i < WORKER; i++) {
        printf("Create worker %d\n", i+1);
        pid_t pid = fork();
        /*child  process */
        if (pid == 0) {
            worker(listenfd, i);
        }
        if (pid < 0) {
            printf("fork error");
        }
    }
    /*wait child process*/
    int status;
    wait(&status);
    return 0;
}