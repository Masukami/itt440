#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char * argv[])
{
	int socket;
	struct sockaddr_in server;
		
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		//find out what's the error
		perror("socket : ");
		exit(-1);
	} 
	//af_inet - domain, sock_stream - tcp, 0 - protocol
        // -1 = error
	
}
