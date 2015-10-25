#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h> //nonblocking socket library
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock, newsock, oldsock, n, i, status;
	struct sockaddr_in server, cli;
	unsigned int len;
	char readBuffer[300];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if ( sock < 0 )
		error("Socket : ");
	
	oldsock = sock;
		
	server.sin_family = AF_INET;
	server.sin_port = htons(3059); //pitfall 4
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	
	//pitfall 3
	int on,ret;
	on = 1;

	ret = setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	
	//pitfall 5
	ret = write ( sock, "Message 1", 50);
	ret = write ( sock, "Message 2", 50);

	len = sizeof(struct sockaddr_in);
		
	if ((bind (sock, (struct sockaddr *)&server, len)) < 0 )
		error("bind");
	if ((listen (sock, 5)) < 0 )
		error("listen");

	if ((newsock = accept(sock, (struct sockaddr *)&cli, &len)) < 0)
		error("accept");

	fcntl (oldsock, F_SETFL, O_NONBLOCK);
	fcntl (newsock, F_SETFL, O_NONBLOCK);

	while(1){
		for ( i = sock; i <= oldsock; i++ ){
			printf("Round number %d\n", i);
			if ( i == sock){
				len = sizeof(struct sockaddr_in);				
				if ((newsock = accept(sock, (struct sockaddr *)&cli, &len))  < 0 )
					error("accept");
				printf("Server : Connection from %s!\n", inet_ntoa(cli.sin_addr));
			fcntl(newsock, F_SETFL, O_NONBLOCK);
			oldsock = newsock;
			}
			else{
				n = recv(newsock, readBuffer, sizeof(readBuffer),0);
				if ( n < 1 ){
					error("recv - non blocking \n");
					printf("Round %d, data read size : %d \n", i, n);
				}
				else{
					readBuffer[n] = '\0';
					printf("String : %s \n", readBuffer);
					if((send(newsock, "Hello from Masukami!\n", 14, 0)) < 1)
						error("send");
				}
			}
		}
		
	
	}

}
