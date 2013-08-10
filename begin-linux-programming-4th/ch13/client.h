/*!
 * \file client.h
 * \brief pipe headers
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-10
 */
/* $Id$ */

#ifndef CLIENT_H
#define CLIENT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO_NAME "/tmp/serv_fifo"
#define CLIENT_FIFO_NAME "/tmp/cli_%d_fifo"

#define BUFFER_SIZE 20

struct data_to_pass_st {
	pid_t client_pid;
	char some_data[BUFFER_SIZE - 1];
};


#endif /* !CLIENT_H */


