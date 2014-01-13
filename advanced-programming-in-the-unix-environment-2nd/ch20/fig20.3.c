/*
 * \file fig20.3.c
 * \brief Create a database and write three records to it
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2014-01-12
 */
/* $Id$ */

#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int main (void)
{
	DBHANDLE	db;

	if ((db = db_open ("fig20.3", O_RDWR | O_CREAT | O_TRUNC,
					FILE_MODE)) == NULL) {
		err_sys ("db_open error");
	}

	if (db_store (db, "Alpha", "data1", DB_INSERT) != 0) {
		err_quit ("db_store error for alpha");
	}
	if (db_store (db, "beta", "Data for beta", DB_INSERT) != 0) {
		err_quit ("db_store error for beta");
	}
	if (db_store (db, "gamma", "record3", DB_INSERT) != 0) {
		err_quit ("db_store error for gamma");
	}

	db_close (db);
	exit (0);
}
