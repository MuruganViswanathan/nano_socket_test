#include "test_common.h"

int main(int argc, char **argv);

int client_socket = -1;

int main(int argc, char **argv) 
{
	int ret = 0;
	int end_point;
	char buf[SIZE_OF_BUFFER];
	int iterations = 128;
        struct timeval t1, t2;
        unsigned long long total_time = 0;
        
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

	while (--iterations) {

            gettimeofday(&t1, NULL);
            nn_send(client_socket, buf, SIZE_OF_BUFFER, 0);
            //printf("Client nn_send() returns %d bytes\n", bytes);
            nn_recv(client_socket, buf, SIZE_OF_BUFFER, 0);
            gettimeofday(&t2, NULL);
            //printf("Client nn_recv() returns %d bytes\n", bytes);
            total_time += (unsigned long long)(t2.tv_sec - t1.tv_sec)*1000000 +
                          (unsigned long long)((t2.tv_usec < t1.tv_usec) ?
                          (t1.tv_usec - t2.tv_usec) : (t2.tv_usec - t1.tv_usec));
	}
	
        printf("\nClient total time for 128 iterations %llu average %llu micro seconds\n", total_time, total_time / 128);
        nn_shutdown(client_socket, end_point);

	return ret;
}
