#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char temp[128];

int receiveBroadcast();
int readPackage();
int connection();

int receiveBroadcast(){
	int socketfd;
	if((socketfd = socket(AF_INET, SOCK_DGRAM,0)) == -1){
		printf("SOCKET FAIL\n");
		return -1;
	}

	int flag = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(struct sockaddr_in));
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(4005);
	client_address.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketfd, (struct sockaddr *) &client_address, sizeof(struct sockaddr))== -1){
		printf("SOCKET BINDING FAIL\n");
		return -1;
	}
	int text_bytes;
	char text[128];
	int addrLen = sizeof(struct sockaddr_in);
	if((text_bytes = recvfrom(socketfd, text, 128,0,(struct sockaddr *)&client_address, &addrLen))!= -1){
		text[text_bytes] = '\0';

		//printf("Broadcast message : %s\n", text);
		printf("Client detected. Client IP : %s\n",inet_ntop(AF_INET,&client_address.sin_addr,temp,sizeof(temp)));
	}	
	else{
		printf("RECEIVING BROADCAST FAIL\n");
	}
	close(socketfd);
	return 0;

}

int readPackage(){

	int socketfd;
	int read_bytes;
	char package[1024];
	struct sockaddr_in server_address;

	if ((socketfd = socket(AF_INET, SOCK_STREAM,0))<0){
		printf("socket error");
	}

	int reuse_flag = 1;
	if (setsockopt(socketfd, SOL_SOCKET,SO_REUSEADDR, (char *)&reuse_flag, sizeof(int)) == -1){
		perror("REUSE CONNECTION FAILED");
	}

		bzero(&server_address,sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(9005);
		
		if(inet_pton(AF_INET, temp,&server_address.sin_addr) <=0){
			printf("inet_pton error");
		}
		if( connect(socketfd, (struct sockaddr*)&server_address, sizeof(server_address))<0){
			printf("connect error\n");
			printf("%s\n",temp);
		}

		return 0;
		close(socketfd);
}


int main(){
		while(1){
		receiveBroadcast();
		readPackage();
	}
}
