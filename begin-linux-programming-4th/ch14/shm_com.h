/*!
 * \file shm_com.h
 * \brief The Share Memory common header
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-11
 */
/* $Id$ */

#ifndef SHM_COM_H
#define SHM_COM_H

#define TEXT_SZ 2048

struct shared_use_st {
	int written_by_you;
	char some_text[TEXT_SZ];
};

#endif /* !SHM_COM_H */


