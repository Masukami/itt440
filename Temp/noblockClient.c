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
	int sock, status, ret;
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
	//pitfall 2
	status = read(sock, buff, sizeof(buff));
	if ( status > 0 )
		printf("Data read from socket!");
	else if ( status < 0 )
		error("read");
	else if ( status == 0 ){
		printf("Peer closed the socket");
		close(sock);
	}

	//sleep 5 seconds
	while(1){
		//pitfall 1
		if ( send(sock, "Hello to Masukami!\n", 14, 0) < 0 )
			error("send");
		else
			printf("Send succeeded!");
	}
	close(sock);
	return 0;
}
