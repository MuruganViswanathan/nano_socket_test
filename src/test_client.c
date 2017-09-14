#include "test_common.h"

int main(int argc, char **argv);

int client_socket = -1;
#define ITERATIONS (1024 * 20)

int main(int argc, char **argv) 
{
	int ret = 0;
	int end_point;
	char buf[SIZE_OF_BUFFER];
	int iterations = ITERATIONS;
        struct timeval t1, t2;
        unsigned long long total_time = 0;
        int opt_value;
        
	client_socket = nn_socket(AF_SP, NN_PAIR);
	if (client_socket < 0) {
		printf("Client Failed to open socket\n");
		return -1;
	}

        opt_value = 1;
        if (nn_setsockopt (client_socket, NN_TCP, NN_TCP_NODELAY, &opt_value, sizeof(opt_value)) < 0)
        {
            printf("Client nn_setsockopt(NN_TCP_NODELAY) Failed\n");
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
            total_time +=  (unsigned long long)((t2.tv_sec *1000000) + t2.tv_usec)
                          -(unsigned long long)((t1.tv_sec *1000000) + t1.tv_usec);
	}
	
        printf("\nClient total time for %d iterations %llu average %llu micro seconds\n",
                ITERATIONS, total_time, total_time / ITERATIONS);
        nn_shutdown(client_socket, end_point);
        nn_close(client_socket);
	return ret;
}
