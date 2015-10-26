#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock, cli, sent;
	unsigned int len;
	struct sockaddr_in server, client;
	sock = socket(AF_INET, SOCK_STREAM, 0); //initialize socket
	if( sock < 0 )
		error("socket : ");
		
	server.sin_family = AF_INET;
	server.sin_port = htons(1036);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	
	len = sizeof(struct sockaddr_in);
	
	if((bind(sock, (struct sockaddr *)&server, len)) < 0 )
		error("bind");
	if( (listen(sock, 5)) < 0 )
		error("listen");
	
	while(1)
	{
		if( (cli = accept(sock, (struct sockaddr *)&client, &len)) < 0)
			error("accept");
	}
	
}
