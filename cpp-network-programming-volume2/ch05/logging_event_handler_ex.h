/// \file logging_event_handler_ex.h
/// \brief The Logging_Event_Handler_Ex class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-06

#ifndef LOGGING_EVENT_HANDLER_EX_H
#define LOGGING_EVENT_HANDLER_EX_H

#include "logging_event_handler.h"

class Logging_Event_Handler_Ex: public Logging_Event_Handler
{
public:
    typedef Logging_Event_Handler PARENT;

    enum { MAX_CLIENT_TIMEOUT = 3600 };

    Logging_Event_Handler_Ex(ACE_Reactor *reactor,
            const ACE_Time_Value &max_client_timeout = ACE_Time_Value(MAX_CLIENT_TIMEOUT)):
        Logging_Event_Handler(reactor),
        time_of_last_log_reacord_(0),
        max_client_timeout_(max_client_timeout) {
    }

    virtual ~Logging_Event_Handler_Ex() {
    }

    virtual int open();
    virtual int handle_input(ACE_HANDLE);
    virtual int handle_timeout(const ACE_Time_Value &tv, const void *act);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

private:
    ACE_Time_Value time_of_last_log_reacord_;
    const ACE_Time_Value max_client_timeout_;
};

#endif /* !LOGGING_EVENT_HANDLER_EX_H */
// vim: set et ts=4 sts=4 sw=4:
