/*!
 * \file remote_loader.h
 * \brief The Remote_Loader class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef REMOTE_LOADER_H
#define REMOTE_LOADER_H

class Remote_Loader
{
public:
    Remote_Loader();
    virtual ~Remote_Loader();

	static int main(int argc, char *argv[]);
};

#endif /* REMOTE_LOADER_H */

