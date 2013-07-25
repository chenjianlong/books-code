/*
 * \file connection1.c
 * \brief demo for connection to MySQL server
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-14
 */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc, char *argv[])
{
	MYSQL *conn_ptr;

	conn_ptr = mysql_init(NULL);
	if (!conn_ptr) {
		fprintf(stderr, "mysql_init failed\n");
		return EXIT_FAILURE;
	}

	conn_ptr = mysql_real_connect(conn_ptr, "localhost", "rick", "secret", "foo", 0, NULL, 0);
	if (conn_ptr) {
		printf("Connection success\n");
	} else {
		printf("Connection failed\n");
	}

	mysql_close(conn_ptr);
	return EXIT_SUCCESS;
}

