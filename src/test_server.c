#include "test_common.h"

int main(int argc, char **argv);

int server_socket = -1;

int main(int argc, char **argv) 
{
	int ret = 0;
	int end_point;

	server_socket = nn_socket(AF_SP, NN_PAIR);
	if (server_socket < 0) {
		printf("Server Failed to open socket\n");
		return -1;
	}

	end_point = nn_bind(server_socket, TCP_URL);

	if (end_point < 0) {
		printf("Server nn_bind(%d, %s) failed\n", server_socket, TCP_URL);
	        nn_close(server_socket);
		return -2;	
	}

	// Need a timer here for clean exit
	while (1) {
		char buf[SIZE_OF_BUFFER];
		int bytes = nn_recv(server_socket, buf, SIZE_OF_BUFFER, 0);
		if (bytes > 0) {
			printf("Server got %d bytes\n", bytes);
		}
	}
        
	nn_shutdown(server_socket, end_point);

	return ret;

}
