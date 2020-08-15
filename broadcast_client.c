#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int sendBroadcast()
{
	char msg[128] = "BROADCAST MSG";
	int socketfd;
	if((socketfd = socket(PF_INET, SOCK_DGRAM, 0))== -1){
		printf("SOCKET FAIL\n");
		return -1;
	}

	int flag = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, &flag, sizeof(int));
	struct sockaddr_in broadcast_address;
	memset(&broadcast_address, 0, sizeof(struct sockaddr_in));
	broadcast_address.sin_family = AF_INET;
	broadcast_address.sin_addr.s_addr = inet_addr("255.255.255.255");
	broadcast_address.sin_port = htons(4005);
	int bytes;
	if((bytes = sendto(socketfd, msg, strlen(msg), 0, (struct sockaddr *)&broadcast_address, sizeof(struct sockaddr))) == -1){
		printf("BROADCAST FAIL");
		return -1;
	}

	close(socketfd);

}

int accept_timeout(int fd, struct sockaddr *addr, unsigned int time){
	int fd_count;
	socklen_t address_length = sizeof(struct sockaddr_in);

	if (time > 0){
		fd_set accept_fdset;
		struct timeval timeout;
		FD_ZERO(&accept_fdset);
		FD_SET(fd, &accept_fdset);
		timeout.tv_sec = time;
		timeout.tv_usec = 0;
		
		do{
			fd_count = select(fd + 1, &accept_fdset, NULL, NULL, &timeout);
		} while (fd_count < 0 && errno == EINTR);
		
		if (fd_count == -1){
			return -1;
		}
		else if(fd_count == 0){
			errno = ETIMEDOUT;
			return -1;
		}
	}

	if (addr != NULL)
		fd_count = accept(fd, (struct sockaddr*)addr, &address_length);
	else
		fd_count = accept(fd, NULL, NULL );

	return fd_count;
}

int discoverIP(){
	int socketfd; 
	int connectionfd;
	struct sockaddr_in server_address;
	char addr[128];
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	
	int reuse_flag = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,(char *)&reuse_flag, sizeof(int)) == -1){
		perror("REUSE CONNECTION FAIL");
	}
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9005);
	
	bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(socketfd, 1024);

	connectionfd = -1;

	while(connectionfd <= 0){
		sendBroadcast();
		connectionfd = accept_timeout(socketfd, (struct sockaddr *)&server_address, 1);
	}

	
	inet_ntop(AF_INET,&server_address.sin_addr,addr,sizeof(addr));	
	printf("Server detected. Server IP : %s\n",addr);

	close(connectionfd);
	
	return 0;
}


int main()
{
	discoverIP();

}