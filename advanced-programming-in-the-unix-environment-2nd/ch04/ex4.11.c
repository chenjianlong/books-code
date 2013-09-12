/*
 * \file ex4.11.c
 * \brief Recursively descend a directory hierarchy, counting file types
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-09-12
 */
/* $Id$ */

#include "apue.h"
#include <dirent.h>
#include <limits.h>

/* function type that is called for each filename */
typedef int Myfunc (const char *, const struct stat *, int);

static Myfunc myfunc;
static int    myftw (char *, Myfunc *);
static int    dopath (const char *, Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main (int argc, char *argv[])
{
	int ret;

	if (argc != 2) {
		err_quit ("usage: ftw <starting-pathname>");
	}

	ret = myftw (argv[1], myfunc); /* does it all */
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0) {
		ntot = 1;  /* avoid divide by 0; print 0 for all counts */
	}
	printf ("regular files  = %7ld, %5.2f %%\n", nreg, (nreg * 100.0) / ntot);
	printf ("drectories     = %7ld, %5.2f %%\n", ndir, (ndir* 100.0) / ntot);
	printf ("block special  = %7ld, %5.2f %%\n", nblk, (nblk* 100.0) / ntot);
	printf ("char special   = %7ld, %5.2f %%\n", nchr, (nchr* 100.0) / ntot);
	printf ("FIFOs          = %7ld, %5.2f %%\n", nfifo, (nfifo* 100.0) / ntot);
	printf ("symbolic links = %7ld, %5.2f %%\n", nslink, (nslink* 100.0) / ntot);
	printf ("sockets        = %7ld, %5.2f %%\n", nsock, (nsock* 100.0) / ntot);

	exit (ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F   1 /* file other than directory */
#define FTW_D   2 /* directory */
#define FTW_DNR 3 /* directory that can't be read */
#define FTW_NS  4 /* file that we can't stat */

static char *begpath; /* the path to begin */

/* we return whatever func() returns */
static int myftw (char *pathname, Myfunc *func)
{
	int len;
	begpath = path_alloc (&len);  /* malloc's for PATH_MAX + 1 bytes */

	strncpy (begpath, pathname, len); /*protect against */
	begpath[len - 1] = 0;			   /* buffer overrun */

	return (dopath (pathname, func));
}

/*
 * Descend through hierarchy, starting at "pathname".
 * If "pathname" is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int dopath (const char *pathname, Myfunc *func)
{
	struct stat		statbuf;
	struct dirent	*dirp;
	DIR				*dp;
	int				ret;

	if (lstat (pathname, &statbuf) < 0) {
		return (func (pathname, &statbuf, FTW_NS));
	}
	if (S_ISDIR (statbuf.st_mode) == 0) { /* not a directory */
		return (func (pathname, &statbuf, FTW_F));
	}

	/* It's a directory. First call func() for the directory,
	 * then process each filename in the directory.
	 */
	if ((ret = func (pathname, &statbuf, FTW_D)) != 0) {
		return ret;
	}

	if ((dp = opendir (pathname)) == NULL) { /* can't read directory */
		return (func (pathname, &statbuf, FTW_DNR));
	}
	if (-1 == chdir (pathname)) {
		return (func (pathname, &statbuf, FTW_DNR));
	}

	while ((dirp = readdir (dp)) != NULL) {
		if (strcmp (dirp->d_name, ".") == 0 ||
			strcmp (dirp->d_name, "..") == 0) {
				continue;
		}
		if ((ret = dopath (dirp->d_name, func)) != 0) {
			break;
		}
	}

	if (closedir (dp) < 0) {
		err_ret ("can't close directory %s", pathname);
	}
	
	if ((strcmp (pathname, begpath) != 0) && (-1 == chdir (".."))) {
		err_quit ("chdir to parent(..) failed");
	}

	return ret;
}

static int myfunc (const char *pathname, const struct stat *statptr, int type)
{
	switch (type) {
	case FTW_F:
		switch (statptr->st_mode & S_IFMT) {
		case S_IFREG:
			nreg++;
			break;
		case S_IFBLK:
			nblk++;
			break;
		case S_IFCHR:
			nchr++;
			break;
		case S_IFIFO:
			nfifo++;
			break;
		case S_IFLNK:
			nslink++;
			break;
		case S_IFSOCK:
			nsock++;
			break;
		case S_IFDIR:
			err_dump ("for S_IFDIR for %s", pathname);
		}
		break;

	case FTW_D:
		ndir++;
		break;

	case FTW_DNR:
		err_ret ("can't read directory %s", pathname);
		break;

	case FTW_NS:
		err_ret ("stat error for %s", pathname);
		break;

	default:
		err_dump ("unknown type %d for pathname %s", type, pathname);
	}
	return 0;
}

