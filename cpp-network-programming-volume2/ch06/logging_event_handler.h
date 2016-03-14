/// \file logging_event_handler.h
/// \brief The Logging_Event_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-05

#ifndef LOGGING_EVENT_HANDLER_H
#define LOGGING_EVENT_HANDLER_H

#include "logging_handler2.h"
#include <ace/Event_Handler.h>

class Logging_Event_Handler: public ACE_Event_Handler
{
public:
    Logging_Event_Handler(ACE_Reactor *reactor):
        ACE_Event_Handler(reactor), logging_handler_(log_file_) {
    }
    
    virtual ~Logging_Event_Handler() {
    }

    virtual int open();

    virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

    virtual ACE_HANDLE get_handle() const;
    ACE_SOCK_Stream& peer() {
        return logging_handler_.peer();
    }

    ACE_FILE_IO& log_file() {
        return log_file_;
    }

protected:
    ACE_FILE_IO log_file_;
    Logging_Handler logging_handler_;
};

#endif /* !LOGGING_EVENT_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
