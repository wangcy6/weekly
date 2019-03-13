#include <sys/socket.h>
#include <string.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
 
#define TRUE  1
#define FALSE 0
 
int main(int argc, char *argv[])
{
    int i, len, rc, on = TRUE;
    int listen_sd, new_sd = 0, max_sd;
    int desc_ready;
    char buffer[80];
    int close_conn, end_server = FALSE;
    struct sockaddr_in server_addr;
    struct timeval timeout;
    struct fd_set master_set, working_set;
 
    // Listen
    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }
 
    // Set socket options
    rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }
 
    // Set IO control
    rc = ioctl(listen_sd, FIONBIO, (char *) &on);
    if (rc < 0)
    {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }
 
    // Bind
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    rc = bind(listen_sd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (rc < 0)
    {
        perror("bind() failed\n");
        close(listen_sd);
        exit(-1);
    }
 
    // Listen
    rc = listen(listen_sd, 32);
    if (rc < 0)
    {
        perror("listen() failed\n");
        close(listen_sd);
        exit(-1);
    }
 
    // Intialize sd set
    FD_ZERO(&master_set);
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);// 向描述符集合添加指定描述符
 
    timeout.tv_sec = 3 * 60;
    timeout.tv_usec = 0;
 
    // Start
    do
    {
        // Copy master_set into working_set
        memcpy(&working_set, &master_set, sizeof(master_set));
 
        printf("Waiting on select()...\n");
        rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);
        if (rc < 0)
        {
            perror("  select() failed\n");
            break;
        }
        if (rc == 0)
        {
            printf("  select() timed out. End program.\n");
            break;
        }
 
        desc_ready = rc; // number of sds ready in working_set
 
        // Check each sd in working_set
        for (i = 0; i <= max_sd && desc_ready > 0; ++i)
        {
            // Check to see if this sd is ready
            if (FD_ISSET(i, &working_set))
            {
                --desc_ready;
 
                // Check to see if this is the listening sd
                if (i == listen_sd)
                {
                    printf("  Listeing socket is readable\n");
                    do
                    {
                        // Accept
                        new_sd = accept(listen_sd, NULL, NULL);
 
                        // Nothing to be accepted
                        if (new_sd < 0)
                        {
                            // All have been accepted
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  accept() failed\n");
                                end_server = TRUE;
                            }
                            break;
                        }
 
                        // Insert new_sd into master_set
                        printf("  New incoming connection - %d\n", new_sd);
                        FD_SET(new_sd, &master_set);
                        if (new_sd > max_sd)
                        {
                            max_sd = new_sd;
                        }
                    }
                    while (new_sd != -1);
                }
                // This is not the listening sd
                else
                {
                    close_conn = FALSE;
                    printf("  Descriptor %d is avaliable\n", i);
					//发送缓冲区和接受缓冲区 大小不一样，需要接收多次
                    do
                    {
                        rc = recv(i, buffer, sizeof(buffer), 0);
 
                        // Receive data on sd "i", until failure occurs
                        if (rc < 0)
                        {
                            // Normal failure
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  recv() failed\n");
                                close_conn = TRUE;
                            }
                            break;
                        }
 
                        // The connection has been closed by the client
                        if (rc == 0)
                        {
                            printf("  Connection closed\n");
                            close_conn = TRUE;
                            break;
                        }
 
                        /* Receiving data succeeded and echo it back
                           the to client */
                        len = rc;
                        printf("  %d bytes received\n", len);
                        rc = send(i, buffer, len, 0);
                        if (rc < 0)
                        {
                            perror("  send() failed");
                            close_conn = TRUE;
                            break;
                        }
                    }
                    while (TRUE);
 
                    // If unknown failure occured
                    if (close_conn)
                    {
                        // Close the sd and remove it from master_set
                        close(i);
                        FD_CLR(i, &master_set);
 
                        // If this is the max sd
                        if (i == max_sd)
                        {
                            // Find the max sd in master_set now
                            while (FD_ISSET(max_sd, &master_set) == FALSE)
                            {
                                --max_sd;
                            }
                        } // End of if (i == max_sd)
                    } // End of if (close_conn)
                }
            }
        }
    }
    while (end_server == FALSE);
 
    /* Close each sd in master_set */
    for (i = 0; i < max_sd; ++i)
    {
        if (FD_ISSET(i, &master_set))
        {
            close(i);
        }
    }
 
    return 0;
}
