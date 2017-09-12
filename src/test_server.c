#include "test_common.h"

int main(int argc, char **argv);

int server_socket = -1;

int main(int argc, char **argv) 
{
	int ret = 0;
	int end_point;
        int opt_value = 30 * 1000; // 30 second timeout 

	server_socket = nn_socket(AF_SP, NN_PAIR);
	if (server_socket < 0) {
		printf("Server Failed to open socket\n");
		return -1;
	}

        if (nn_setsockopt (server_socket, NN_SOL_SOCKET, NN_RCVTIMEO, &opt_value, sizeof(opt_value)) < 0)
        {
            printf("Server nn_setsockopt(NN_RCVTIMEO) Failed\n");
        }

        opt_value = 1;
        if (nn_setsockopt (server_socket, NN_TCP, NN_TCP_NODELAY, &opt_value, sizeof(opt_value)) < 0)
        {
            printf("Server nn_setsockopt(NN_TCP_NODELAY) Failed\n");
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
		} else {
                    // we timed out or there is an error
                    printf("Server timed out or got an error, terminating\n");
                    ret = -3;
                    break;
                }
	}
        
	nn_shutdown(server_socket, end_point);

	return ret;

}
