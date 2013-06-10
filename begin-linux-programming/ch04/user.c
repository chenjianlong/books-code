/*
 * \file user.c
 * \brief extracts some user information from the password database
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-06
 */
/* $Id$ */

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	uid_t uid;
	gid_t gid;

	struct passwd *pw;
	uid = getuid();
	gid = getgid();

	printf("User is %s\n", getlogin());

	printf("User IDs: uid=%d gid=%d\n", uid, gid);

	pw = getpwuid(uid);
	printf("UID passwd entry:\n name=%s, uid=%d, gid=%d, home=%s, shell=%s gecos=%s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell, pw->pw_gecos);

	pw = getpwnam("root");
	printf("root passwd entry:\n");
	printf("name=%s, uid=%d, gid=%d, home=%s, shell=%s, gecos=%s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell, pw->pw_gecos);

	exit(0);
}	

