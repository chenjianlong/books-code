/*
 * \file copy_system.c
 * \brief demo of use system call to read and write file char by char
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-03
 */
/* $Id$ */

#include <unistd.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>

int main() 
{
	char c;
	int in, out;
	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR); 
	while(read(in,&c,1) == 1) {
		write(out,&c,1);
	}

	exit(0); 
}

