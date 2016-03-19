/// \file ac_output_handler.h
/// \brief The AC_Output_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-18

#ifndef AC_OUTPUT_HANDLER_H
#define AC_OUTPUT_HANDLER_H

#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Log_Record.h>

class AC_CLD_Connector;

class AC_Output_Handler: public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_MT_SYNCH>
{
public:
    enum { QUEUE_MAX = sizeof(ACE_Log_Record) * ACE_IOV_MAX };

    virtual int open(void*);
    virtual int put(ACE_Message_Block*, ACE_Time_Value* = 0);

protected:
    AC_CLD_Connector *connector_;

    virtual int handle_input(ACE_HANDLE handle);
    virtual int svc();
    virtual int send(ACE_Message_Block *chunk[], size_t &count);
};

#ifndef FLUSH_TIMEOUT
#   define FLUSH_TIMEOUT 10
#endif /* FLUSH_TIMEOUT */

#endif /* !AC_OUTPUT_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
