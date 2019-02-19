#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>


#define PORT 8080

int main()
{
	int sockfd, newsock;
	int opt=1;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	if( (sockfd = socket(AF_INET,SOCK_STREAM ,0)) == 0)
	{
		perror("socket");
		exit(-1);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR ,
			&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(-1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = PORT;

	//bind
	if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind");
		exit(-1);
	}


	//listen
	if(listen(sockfd, 3) < 0 )
	{
		perror("listen");
		exit(-1);
	}


	//accept
	newsock = accept(sockfd, (struct sockaddr*)&address, &addrlen);
	if(newsock < 0)
	{
		perror("accept");
		exit(-1);
	}

	read(newsock, buffer, 1024);
	printf("%s\n", buffer);
	send(newsock, hello, strlen(hello), 0);
	return 0;

}
