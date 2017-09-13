#ifndef _TEST_COMMON_H_
#define _TEST_COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif

#define TCP_PROTOCOL "tcp://"
	/* TCP Port number */
#define TCP_PORT "9999"

	/* Using local IP */
#define IP_ADDRESS "127.0.0.1"

	/* For simplicity define the whole TCP url */
#define TCP_URL_CLIENT "tcp://127.0.0.1:9999"
#define TCP_URL "tcp://*:9999"


#ifdef __cplusplus
}
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <getopt.h>

#include <nanomsg/nn.h>
#include <nanomsg/tcp.h>
#include <nanomsg/pair.h>

#define SIZE_OF_BUFFER 1024

#endif
