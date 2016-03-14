/// \file logging_handler.h
/// \brief Logging Handler
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-07

#ifndef LOGGING_HANDLER2_H
#define LOGGING_HANDLER2_H

#include <ace/FILE_IO.h>
#include <ace/SOCK_Stream.h>

class ACE_Message_Block;

class Logging_Handler
{
public:
    Logging_Handler(ACE_FILE_IO &log_file): log_file_(log_file) {
    }

    Logging_Handler(ACE_FILE_IO &log_file,
                    ACE_HANDLE handle): log_file_(log_file) {
        logging_peer_.set_handle(handle);
    }

    Logging_Handler(ACE_FILE_IO &log_file, const ACE_SOCK_Stream &logging_peer):
        log_file_(log_file), logging_peer_(logging_peer) {
    }

    int close() {
        return logging_peer_.close();
    }

    int recv_log_record(ACE_Message_Block *&mblk);
    int write_log_record(ACE_Message_Block *mblk);

    int log_record();

    ACE_SOCK_Stream &peer() {
        return logging_peer_;
    }

private:
    ACE_FILE_IO &log_file_;
    ACE_SOCK_Stream logging_peer_;
};

#endif /* !LOGGING_HANDLER2_H */
// vim: set et ts=4 sts=4 sw=4:
