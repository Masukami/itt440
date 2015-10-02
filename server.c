#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //for socket
#include <sys/socket.h>
#include <netinet/in.h> //for struct
#include <errno.h> //for error

int main(int argc, char * argv[])
{
	int socket,len;
	struct sockaddr_in server;
		
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		//find out what's the error
		perror("socket : ");
		exit(-1);
	} 
	//af_inet - domain, sock_stream - tcp, 0 - protocol
        // -1 = error

	server.sin_family = AF_INET;
	server.sin_port = htons(1036);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(struct sockaddr_in);
	// error checking for bind
	if((bind (sock, (struct sockaddr *)&server, len)) == -1)
	{
		perror("bind");
		exit(-1);
	}	
	if((listen (sock, 5)) == -1)
	{
		perror("listen");
		exit(-1);
	}
}
