/*
 * \file ex15.12.c
 * \brief create message queue and delete it
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <sys/msg.h>

#define DEFMODE 0600

struct mymsg {
	long mtype;
	char mtext[512];
};

int main (void)
{
	int i = 0, msgid;
	struct mymsg msg;

	for (i = 0; i < 5; i++) {
		msgid = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | DEFMODE);
		if (-1 == msgid) {
			err_sys ("msgget failed");
		}
		printf ("msgid: %d\n", msgid);

		if (-1 == msgctl (msgid, IPC_RMID, NULL)) {
			err_sys ("msgctl failed");
		}
	}

	for (i = 0; i < 5; i++) {
		msgid = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | DEFMODE);
		if (-1 == msgid) {
			err_sys ("msgget failed");
		}
		printf ("msgid: %d\n", msgid);

		msg.mtype = i + 1;

		if (-1 == msgsnd (msgid, &msg, sizeof (struct mymsg), 0)) {
			err_sys ("msgsnd failed");
		}
	}
	exit (0);
}
