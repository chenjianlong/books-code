/*
 * \file print_dir.c
 * \brief demo of using print dir
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-03
 */
/* $Id$ */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void print_dir(char *dir, int depth) 
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return; 
	}

	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but ignore . and .. */ 
			if(strcmp(".", entry->d_name) == 0 || 
					strcmp("..", entry->d_name) == 0) {
				continue;
			}

			printf("%*s%s/\n", depth, "", entry->d_name); 
			/* Recurse at a new indent level */ 
			print_dir(entry->d_name,depth+4);
		} else {
			printf("%*s%s\n", depth, "", entry->d_name); 
		}
	}

	chdir("..");
	closedir(dp); 
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <dir-to-print>\n", argv[0]);
		exit(-1);
	}

	printf("Directory scan of %s:\n", argv[1]); 
	print_dir(argv[1], 0); 
	printf("done.\n");

	exit(0); 
}
