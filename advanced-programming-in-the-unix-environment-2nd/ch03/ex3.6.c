/*
 * \file ex3.6.c
 * \brief verify to exercise 3.6
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-29
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";
	char buf_read[11] = {'\0'};
	int n = 0;

	int fd = open("test.dat", O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0666);

	if (-1 == fd) {
		err_sys("can not open file");
	}

	write(fd, buf1, 10);
	write(fd, buf2, 10);
	lseek(fd, 0, SEEK_SET);
	n = read(fd, buf_read, 10);
	buf_read[n] = '\0';
	printf("read file from offset 0: %s\n", buf_read);

	/* seek file to offset 10 */
	lseek(fd, 10, SEEK_SET);
	/* write buf1 to it */
	write(fd, buf1, 10);

	/* seek file to offset 10 */
	lseek(fd, 10, SEEK_SET);
	/* read it */
	n = read(fd, buf_read, 10);
	buf_read[n] = '\0';
	printf("read file from offset 10: %s\n", buf_read);

	exit(0);
}

