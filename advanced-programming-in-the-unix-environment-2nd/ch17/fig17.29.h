/*!
 * \file fig17.29.h
 * \brief The opend.h header,version 1
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-24
 */
/* $Id$ */

#ifndef FIG17_29_H
#define FIG17_29_H

#include "apue.h"
#include <errno.h>

#define CL_OPEN "open"			/* client's request for server */

extern char errmsg[];			/* error message string to return to client */
extern int	oflag;				/* open() flag: O_xxx ... */
extern char *pathname;			/* of file to open() for client */

int cli_args (int, char **);
void request (char *, int, int);

#endif /* !FIG17_29_H */
