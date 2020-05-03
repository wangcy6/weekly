#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_function(void *arg);
int main() {
    int listenfd, *connfdp;
    socklen_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    pthread_t th;
    // 创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // 命名套接字
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(6240);
    server_len = sizeof(server_address);
    bind(listenfd, (struct sockaddr*)&server_address, server_len);
    // 创建套接字队列
    listen(listenfd, 5);
    // 接受客户的连接
    while (1) {
        printf("server waiting\n");
        connfdp = malloc(sizeof(int));
        client_len = sizeof(client_address);
        *connfdp = accept(listenfd, (struct sockaddr*)&client_address, &client_len);
        // 创建新线程
        pthread_create(&th, NULL, thread_function, connfdp);
    }
}
void *thread_function(void *arg) {
    int connfd = *((int*)arg);
    printf("Thread_function is running. Argument was %d\n", connfd);
    pthread_detach(pthread_self());
    free(arg);
    // 处理客户的请求
    char ch;
    read(connfd, &ch, 1);
    ch++;
    write(connfd, &ch, 1);
    close(connfd);
    return NULL;
}

//只要线程执行pthread_exit(),整个线程就会结束，并且释放占用资源，为什么还要区分detach模式呢，
//感觉没有任何区别呀，高性能服务器 你们一般采用哪个方式
