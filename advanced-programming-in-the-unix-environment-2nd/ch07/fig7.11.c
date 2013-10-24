/*
 * \file fig7.11.c
 * \brief Example of setjmp and longjmp
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-24
 */
/* $Id$ */

#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5

void do_line (char *);
void cmd_add (void);
int get_token (void);

jmp_buf jmpbuffer;

int main (void)
{
	char line[MAXLINE];

	if (setjmp (jmpbuffer) != 0) {
		printf ("error");
	}
	while (fgets (line, MAXLINE, stdin) != NULL) {
		do_line (line);
	}
	exit (0);
}

char *tok_ptr;

void do_line (char *ptr)
{
	int cmd;

	tok_ptr = ptr;
	while ((cmd = get_token ()) > 0) {
		switch (cmd) {
		case TOK_ADD:
			cmd_add ();
			break;
		}
	}
}

void cmd_add (void)
{
	int token;

	token = get_token ();
	if (token == TOK_ADD) {
		longjmp (jmpbuffer, 1);
	}
	/* reset of processing for this command */
}

int get_token (void)
{
	/* fetch next token from line pointed to by tok_ptr */
	return TOK_ADD;
}

