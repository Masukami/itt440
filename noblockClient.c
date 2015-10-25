#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock, numbytes;
	char buff[300];
	struct hostent *host;
	struct sockaddr_in server;

	if (argc != 2){
		printf("Enter client hostname!\n");
		exit(1);
	}
			
	if (( host = gethostbyname (argv[1])) == NULL)
		error("gethostbyname");
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 1 )
		error("Socket : ");

	server.sin_family = AF_INET;
	server.sin_port = htons(3059);
	bzero(&server.sin_zero, 8);	
	server.sin_addr = *((struct in_addr *)host->h_addr);
		
	if (connect (sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0)
		error("connect");
	
	//sleep 5 seconds
	while(1){
		if ( send(sock, "Hello to Masukami!\n", 14, 0) < 0 )
			error("send");
		}
	close(sock);
	return 0;
}
