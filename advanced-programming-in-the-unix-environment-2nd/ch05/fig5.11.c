/*
 * \file fig5.11.c
 * \brief Print buffering for various standard I/O streams
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-15
 */
/* $Id$ */

#include "apue.h"

void pr_stdio (const char *, FILE *);

int main (void)
{
	FILE *fp;

	fputs ("enter any character\n", stdout);
	if (getchar () == EOF) {
		err_sys ("getchar error");
	}
	fputs ("one line to standard error\n", stderr);

	pr_stdio ("stdin", stdin);
	pr_stdio ("stdout", stdout);
	pr_stdio ("stderr", stderr);

	if ((fp = fopen ("/etc/motd", "r")) == NULL) {
		err_sys ("fopen error");
	}
	if (getc (fp) == EOF) {
		err_sys ("getc error");
	}
	pr_stdio ("/etc/motd", fp);
	exit (0);
}

void pr_stdio (const char *name, FILE *fp)
{
	printf ("stream = %s, ", name);
	/* The following is noportable. */
	if (fp->_IO_file_flags & _IO_UNBUFFERED) {
		printf ("unbuffered");
	} else if (fp->_IO_file_flags & _IO_LINE_BUF) {
		printf ("line buffered");
	} else {
		printf ("fully buffered");
	}
	printf (", buffer size = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

