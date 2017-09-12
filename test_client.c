#include "test_common.h"

int main(int argc, char **argv);

int client_socket = -1;

int main(int argc, char **argv) 
{
	int ret = 0;
	int end_point;
	char buf[SIZE_OF_BUFFER];
	int bytes;


	client_socket = nn_socket(AF_SP, NN_PAIR);
	if (client_socket < 0) {
		printf("Client Failed to open socket\n");
		return -1;
	}


	end_point = nn_connect(client_socket, TCP_URL);

	if (end_point < 0) {
		printf("Client nn_connect(%d, %s) failed\n", client_socket, TCP_URL);
	        nn_close(client_socket);
		return -2;	
	}

	bytes = nn_send(client_socket, buf, SIZE_OF_BUFFER, 0);

	printf("Client nn_send() returns %d bytes\n", bytes);

        nn_shutdown(client_socket, end_point);

	return ret;
}
