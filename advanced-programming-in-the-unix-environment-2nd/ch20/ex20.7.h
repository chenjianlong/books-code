/*!
 * \file ex20.7.h
 * \brief The apue_db common function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2014-01-09
 */
/* $Id$ */

#ifndef APUE_DB_H
#define APUE_DB_H

typedef		void * DBHANDLE;

DBHANDLE	db_open (const char *, int, int, ...);
void		db_close (DBHANDLE);
char	   *db_fetch (DBHANDLE, const char *);
int			db_store (DBHANDLE, const char *, const char *, int);
int			db_delete (DBHANDLE, const char *);
void		db_rewind (DBHANDLE);
char	   *db_nextrec (DBHANDLE, char *);

/*
 * Flags for db_store ().
 */
#define DB_INSERT		1	/* insert new record only */
#define DB_REPLACE		2	/* replace existing record */
#define DB_STORE		3	/* replace or insert */

/*
 * Implementation limits.
 */
#define IDXLEN_MIN		6	/* key, sep, start, sep, length, \n */
#define IDXLEN_MAX	 1024	/* arbitrary */
#define DATLEN_MIN		2	/* data byte, newline */
#define DATLEN_MAX	 1024	/* ARBITRARY */

#endif /* !APUE_DB_H */
