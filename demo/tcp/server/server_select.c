/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/* This program uses the Select function to control sockets            */
/* First, the vectors of file descriptors (fd) will be set in order to */
/* load the select function with the appropriate fds.                  */
/*                                                                     */
/* The select command accepts 4 parameters:                            */
/*     - fds that are load for reading                                 */
/*     - fds that are load for writing                                 */
/*     - fds that are load for exception handling                      */
/*                                                                     */
/* after the connection is established an iinfinite loop with the      */
/* client work permanently.                                            */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <errno.h> 
    #include <string.h> 
    #include <sys/types.h> 
    #include <netinet/in.h> 
    #include <sys/socket.h> 
    #include <sys/wait.h> 
    #include <sys/time.h>
    #include <unistd.h>

    #define MYPORT 3490    	/* the port users will be connecting to */
    #define MAXDATASIZE 100	/*The maximum message passed */
    #define BACKLOG 10     	/* how many pending connections queue will hold */

    main()
    {
        struct 	sockaddr_in 	my_addr;    			/*My address information 			   */
        struct 	sockaddr_in 	their_addr; 			/*Connector's address information 	           */
	struct 	timeval 	tv;				/*The time wait for socket to be changed	   */
	struct 	timezone	tz;				/*The time zone we are using 			   */
	struct 	timeval 	measure_tv_before;		/*The time wait for socket to be changed	   */
	struct 	timezone	measure_tz_before;		/*The time zone we are using 			   */
	struct 	timeval 	measure_tv_after;		/*The time wait for socket to be changed	   */
	struct 	timezone	measure_tz_after;		/*The time zone we are using 			   */
    fd_set 			readfds, writefds, exceptfds; 	/*File descriptors for read, write and exceptions  */
        int 			new_fd;  			/*The new file descriptor returned from accept	   */
        int 			sockfd;  			/*The first file descriptor given for communication*/
	int			j;				/*Index used for fd counter			   */	
        int 			sin_size;			/*Size of struct internet input address		   */
	int			numbytes;			/* Number of bytes received in each packet         */
	int			sock;				
	int			sock_to_read;			/* File descriptor ready for reading		   */
	int			max_fd;				/* Number of socket fd that are in use		   */
        char                    buf[MAXDATASIZE];       	/*The string to be passed 			   */

	
	/*Initiate the read, write, except structs */
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        my_addr.sin_family = AF_INET;         /* host byte order */
        my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
        my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
        bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) \
                                                                      == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }

	max_fd = sockfd;
	FD_SET(sockfd, &readfds); /*Add sock_fd to the set of file descriptors to read from */
	    		FD_ZERO(&readfds);
	    		FD_ZERO(&writefds);
	    		FD_ZERO(&exceptfds);
	    		for(j=sockfd;j<=max_fd;j++){
				FD_SET(j,&readfds);
				printf ("Setup fd number %d \n",j);
	    		}

        while(1) {  /* main accept() loop */	
		/*--------------------------------------*/
		/* Initiate the FD vector & set values	*/
		/*--------------------------------------*/

	    gettimeofday(&measure_tv_before,&measure_tz_before);
	    printf("Before select ...time is: %ld, %ld\n",tv.tv_sec,tv.tv_usec);
	    tv.tv_sec = 5; 		/*Initiate time to wait for fd to change */
	    if ((sock = select(max_fd+1 , &readfds, &writefds, &exceptfds, &tv)) < 0) { 
               perror("select");
               continue;
       	    }
	    gettimeofday(&measure_tv_after,&measure_tz_after);
	    printf("After select again...time in select:  %ld sec and %ld usec\n", \
			measure_tv_after.tv_sec - measure_tv_before.tv_sec ,measure_tv_after.tv_usec - measure_tv_before.tv_usec);
	    printf("Sock value is (after select) :%d \n",sock);
	
	    /*Checking which FD are set */

	    if(FD_ISSET(sockfd, &readfds)){ /* If sockfd is changed, new conenciton is requested */
					    /* Reading and writing is done to other fds		 */
            	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, \
                                                          &sin_size)) == -1) {
                	perror("accept");
                	continue;
            	}
		max_fd = new_fd;
            	printf("server: got connection from %s\n", \
                                               inet_ntoa(their_addr.sin_addr));
		FD_SET(new_fd, &readfds); /*Add sock_fd to the set of file descriptors to read from */
		FD_CLR(sockfd, &readfds); /*Add sock_fd to the set of file descriptors to read from */
		printf("Ending the connect function %ld, %ld\n",tv.tv_sec,tv.tv_usec);
	    }
	    else {
		    /*Check which FD are set */
		    for (j=sockfd;j<=max_fd && sock > 0;j++){	/*The loop starts from the first comm fd */
			    printf("Checking now j=%d, readfs(j) status =%d \n", j, FD_ISSET(j, &readfds));
			if (FD_ISSET(j, &readfds) == 1 ) {
				sock_to_read = j;
				if ((numbytes=recv(sock_to_read, buf, MAXDATASIZE, 0)) == -1) {/*Receive info from the server*/
                	    		perror("recv");
                    			exit(1);
	                	}
				buf[numbytes] = '\0';
				printf("recv: sock=%d, buf=%s \n", sock,buf); 
            			if (send(sock_to_read , "Hello, world!\n", 14, 0) == -1)
                		 	perror("send in loop");
				FD_CLR(sock_to_read, &readfds);
				sock--; /* We found one fd that was changed form select	*/
                                for(j=sockfd;j<=max_fd;j++)
					FD_SET(j,&readfds);
			}
		    } 	
	    }

	}
            close(new_fd);

        
    }

//https://popozhu.github.io/2013/06/09/Libevent_%E7%AC%AC2%E8%8A%82_%E8%AF%B4%E8%AF%B4%E5%BC%82%E6%AD%A5io/