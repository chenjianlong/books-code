/// \file logging_handler.h
/// \brief Logging Handler
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-07

#ifndef LOGGING_HANDLER_H
#define LOGGING_HANDLER_H

#include <ace/SOCK_Stream.h>

class ACE_Message_Block;

class Logging_Handler
{
public:
    Logging_Handler(ACE_HANDLE handle)  {
        logging_peer_.set_handle(handle);
    }

    int close() {
        return logging_peer_.close();
    }

    int recv_log_record(ACE_Message_Block *&mblk);

    ACE_SOCK_Stream &peer() {
        return logging_peer_;
    }

private:
    ACE_SOCK_Stream logging_peer_;
};

#endif /* !LOGGING_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
