/*
 * \file copy_block.c
 * \brief this file is use to test the performance of use low-level API 1K block by block to copy file
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-02
 */
/* $Id$ */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	char block[1024];
	int in, out;
	int nread;

	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	while ((nread = read(in, block, sizeof(block))) > 0) {
		write(out, block, nread);
	}

	exit(0);
}


