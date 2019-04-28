#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include "Mutex.h"

int GetPipeBufferSize(){
    int pipe_fd[2];  
    if (pipe(pipe_fd) < 0){  
        printf("pipe create error\n");  
        return 0;;  
    }
    int len = 0;
    fcntl(pipe_fd[1], F_SETFL, O_NONBLOCK);//设置为非阻塞    
    for (;;){
        int sz = write(pipe_fd[1], "a", 1);
        if (sz == 1){  
            len++;    
        }else{
            break;
        }
    }  
    close(pipe_fd[0]);  
    close(pipe_fd[1]); 
    return len;
}

static int pipeWrite = 0;
static int pipeRead = 0;
CountDownLatch cond(1);//倒计时

static int msgSize = 0;
static int loopNum = 10;

static void* ThreadWrite(void* idx){
    cond.Wait();
    char c = 'a';
    c = (int)c + (int)*(int*)idx;
    char* buff = (char*)malloc(msgSize);
    memset(buff, c, msgSize);
    for (int i=0; i<loopNum; i++){
        write(pipeWrite, buff, msgSize);
    }
    free(buff);
    return NULL;
}

static void* ThreadRead(void* idx){
    cond.Wait();
    int count = 0;
    char* buff = (char*)malloc(msgSize);
    for (;;){
        int n = read(pipeRead, buff, msgSize);
        if (n < 0){
            continue;
        }
        assert(n == msgSize);
        for (int i=1; i<msgSize; i++){
            assert(buff[i] == buff[0]);
        }
        if (++count >= loopNum * 99){
            break;
        }
    }
    free(buff);
    return NULL;
}

void TestPipeAtomic(){
    int pipe_fd[2];  
    if (pipe(pipe_fd) < 0){  
        printf("pipe create error\n");  
        exit(1);  
    }
    pipeRead = pipe_fd[0];
    pipeWrite = pipe_fd[1];

    pthread_t pid[100];
    for (int i=0; i<99; i++){
        if (pthread_create(&pid[i], NULL, ThreadWrite, (void*)&i)){
            printf("Create thread failed.\n");
            exit(1);
        }     
    }
    if (pthread_create(&pid[99], NULL, ThreadRead, NULL)){
        printf("Create thread failed.\n");
        exit(1);
    }     

    cond.CountDown();//读写线程同时启动

    for (int i=0; i<99; i++){
        pthread_join(pid[i], NULL);
    }
    pthread_join(pid[99], NULL);

    close(pipe_fd[0]);  
    close(pipe_fd[1]); 
}


int main(int argc, char *argv[]){  
    int sz = GetPipeBufferSize();  
    printf("pipi buffer size = %fkb\n", sz/1024.0);

    for (msgSize=4000; true; msgSize++){
        TestPipeAtomic();
        printf("operation is atomic while write size = %d\n", msgSize);
    }

    return 0;  
}  
