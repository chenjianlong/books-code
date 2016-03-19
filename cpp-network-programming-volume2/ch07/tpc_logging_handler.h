/// \file tpc_logging_handler.h
/// \brief The Tpc_Logging_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-15

#ifndef TPC_LOGGING_HANDLER_H
#define TPC_LOGGING_HANDLER_H

#include "logging_handler.h"
#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>

class TPC_Logging_Handler: public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_NULL_SYNCH>
{
public:
    TPC_Logging_Handler(): logging_handler_(log_file_) {
    }

    virtual int open(void*);
    virtual int svc();

protected:
    ACE_FILE_IO log_file_;
    Logging_Handler logging_handler_;
};

#endif /* !TPC_LOGGING_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
