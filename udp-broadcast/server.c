/*
	This code acts like a simple broadcast listener.
	Its responsibility is to share which port the applicaion running on.

	It waits for incoming packages which include client_key in a loop.
	It checks the key when a package recieved.
	If the key is correct, the server send back the server_key and port number seperately.
	Then it starts to wait new packages.

	The keys are used for a simple authentication. I just wanted to make sure that the data come from our clients or the server.
	The private keys are randomly generated and hardcoded.
*/

// TODO: Get the IP address of the server with an efficient method
// TODO: Detailed and efficent error handling (in loop)
// TODO: Write logs into a file instead of stdout
// TODO: Windows compatibility (additional for server)

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

#define BROADCAST_PORT 9000	// Broadcast port
#define TCP_PORT 9005	// TCP port

const char client_key[16] = "6Unz2hcxQVTs2dq\0"; // A random private key which declare the broadcast come from our clients
const char server_key[16] = "R8Jb2f55EZDAmJ7\0"; // A random private key which declare the reply come from the server

int stop, socket_fd;

int broadcast_listener();
void signal_handler(int signal);

int main() {
	int result;

	signal(SIGINT, signal_handler); // Interrupt handler, closes the socket

	result = broadcast_listener(); // Listen broadcast port until interrupt
	if (result != 0)
		printf("Broadcast listener failed: %s\n", strerror(result));

	return 0;
}

/* ---------------------------------------- */

int broadcast_listener() {
	char buffer[16];
	uint16_t port;
	int flag, address_length;
	struct sockaddr_in client_address;

	port = TCP_PORT;
	flag = 1;
	address_length = sizeof(struct sockaddr);
	memset(&client_address, 0, sizeof(struct sockaddr_in));

	// Create UDP socket
	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		return errno;

	// Configure socket for broadcasting
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1) {
		close(socket_fd);
		return errno;
	}

	// Address configuration
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(BROADCAST_PORT);
	client_address.sin_addr.s_addr = INADDR_ANY;

	// Bind to socket
	if (bind(socket_fd, (struct sockaddr *) &client_address, sizeof(struct sockaddr)) == -1)  {
		close(socket_fd);
		return errno;
	}

	// Wait for request in a loop
	while (!stop) {
		if (recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address, (unsigned int *) &address_length) == -1)
			continue;

		if (strcmp(client_key, buffer) != 0)
			continue;

		if (sendto(socket_fd, &server_key, sizeof(server_key), 0, (struct sockaddr *) &client_address, sizeof(struct sockaddr)) == -1)
			continue;

		if (sendto(socket_fd, &port, sizeof(port), 0, (struct sockaddr *) &client_address, sizeof(struct sockaddr)) == -1)
			continue;

		printf("Server information shared with %s\n", inet_ntoa(client_address.sin_addr));
	}

	return 0;
}

/* ---------------------------------------- */

void signal_handler(int signal) {
	stop = 1;
	printf("\n%s signal received.\n", sys_siglist[signal]);
	close(socket_fd);
  exit(0);
}
