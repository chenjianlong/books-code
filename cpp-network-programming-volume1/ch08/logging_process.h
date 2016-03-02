/// \file logging_process.h
/// \brief The Logging_Process class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-02

#ifndef LOGGING_PROCESS_H
#define LOGGING_PROCESS_H

#include <ace/Process.h>
#include <ace/SOCK_Stream.h>

class Logging_Process: public ACE_Process
{
public:
    Logging_Process(const char *prog_name,
                    const ACE_SOCK_Stream &logging_peer);

    virtual int prepare(ACE_Process_Options &options);
    virtual void unmanage();

private:
    Logging_Process();

private:
    char prog_name_[MAXPATHLEN + 1];
    ACE_SOCK_Stream logging_peer_;
};

#endif /* !LOGGING_PROCESS_H */
// vim: set et ts=4 sts=4 sw=4:
