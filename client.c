#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT 8080

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

	//socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}

	//connect
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = PORT;

	if(inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr) < 0)
	{
		perror("pton");
		exit(-1);
	}

	if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
	{
		perror("connect");
		exit(-1);
	}
	//send
	send(sockfd, hello, strlen(hello), 0);
	read(sockfd, buffer, 1024);
	printf("from Server - %s\n", buffer);

	return 0;

}
