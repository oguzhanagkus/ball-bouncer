/*
	This code performs a simple network discovery operation, it looks for a spesific application server.
	It broadcasts the client_key on a local network. After that it starts to wait for server information until timeout.
	The server checks the client_key when it recieved. If the key is correct, the server send back the server_key and port number seperately.
	The client checks the server_key when it recieved. If the key is correct, then the client gets the port number.
	Finally, we have server's IP address and the port number that our application server runs on.

	The keys are used for a simple authentication. I just wanted to make sure that the data come from our clients or the server.
	The private keys are randomly generated and hardcoded.
*/

// TODO: Detailed and efficent error handling
// TODO: Windows compatibility (mandatory for client)

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TIMEOUT 10 // Timeout value in seconds, waits for server information until timeout
#define BROADCAST_PORT 9000	// Broadcast port
#define BROADCAST_IP "255.255.255.255" // Broadcast IP

const char client_key[16] = "6Unz2hcxQVTs2dq\0"; // A random private key which declare the broadcast come from our clients
const char server_key[16] = "R8Jb2f55EZDAmJ7\0"; // A random private key which declare the reply come from the server

int socket_fd;

int discover_server(struct sockaddr_in *server_address);
void signal_handler(int signal);

int main() {
	int result;
	struct sockaddr_in server_address; // Includes address family, port number and IP adress

	signal(SIGINT, signal_handler); // Interrupt handler, closes the socket

	result = discover_server(&server_address); // Try to discover server

	if (result == 0)
		printf("IP: %s - Port: %d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
	else if (result == -1)
		printf("Authentication failed! Invalid key recieved.\n");
	else
		printf("Server discovery failed: %s\n", strerror(result));

	return 0;
}

/* ---------------------------------------- */

// Returns 0 on success, -1 on authentication error, 'errno' on other situations
int discover_server(struct sockaddr_in *server_address) {
	char buffer[16];
	uint16_t port;
	int flag, address_length;
	struct timeval timeout;
	struct sockaddr_in target_address;

	flag = 1;
	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	address_length = sizeof(struct sockaddr);
	memset(&target_address, 0, sizeof(struct sockaddr_in));

	// Create UDP socket
	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		return errno;

	// Configure socket for broadcasting
	if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, &flag, sizeof(flag)) == -1) {
		close(socket_fd);
		return errno;
	}

	// Address configuration
	target_address.sin_family = AF_INET;
	target_address.sin_port = htons(BROADCAST_PORT);
	target_address.sin_addr.s_addr = inet_addr(BROADCAST_IP);

	// Broadcast client key
	if (sendto(socket_fd, &client_key, sizeof(client_key), 0, (struct sockaddr *) &target_address, sizeof(struct sockaddr)) == -1)  {
		close(socket_fd);
		return errno;
	}

	// Configure socket to timeout
	if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
		close(socket_fd);
		return errno;
	}

	// Firstly try to get server_key, then check the key, finally get the server info
	if (recv(socket_fd, buffer, sizeof(buffer), 0) == -1) {
		close(socket_fd);
		return errno;
	}

	if (strcmp(server_key, buffer) != 0) {
		close(socket_fd);
		return -1;
	}

	if (recvfrom(socket_fd, &port, sizeof(port), 0, (struct sockaddr *) server_address, (unsigned int *) &address_length) == -1)  {
		close(socket_fd);
		return errno;
	}

	server_address->sin_port = htons(port);

	close(socket_fd);
	return 0;
}

/* ---------------------------------------- */

void signal_handler(int signal) {
	printf("\n%s signal received.\n", sys_siglist[signal]);
	close(socket_fd);
  exit(0);
}
