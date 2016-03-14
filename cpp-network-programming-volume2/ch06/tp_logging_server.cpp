#include "tp_logging_server.h"
#include "tp_logging_task.h"
#include <ace/ACE.h>
#include <ace/Reactor.h>

int TP_Logging_Server::init(int argc, ACE_TCHAR *argv[])
{
    int i;
    char **array = 0;

    ACE_NEW_RETURN(array, char*[argc], -1);
    ACE_Auto_Array_Ptr<char*> char_argv(array);

    for (i = 0; i < argc; ++i)
        char_argv[i] = ACE::strnew(ACE_TEXT_ALWAYS_CHAR(argv[i]));

    ACE_NEW_NORETURN(logging_dispatcher_,
            TP_Logging_Server::LOGGING_DISPATCHER(
                i, char_argv.get(), ACE_Reactor::instance()));

    for (i = 0; i < argc; ++i) ACE::strdelete(char_argv[i]);

    if (logging_dispatcher_ == 0) {
        return -1;
    } else {
        return TP_LOGGING_TASK::instance()->open();
    }
}

int TP_Logging_Server::fini()
{
    TP_LOGGING_TASK::instance()->flush();
    TP_LOGGING_TASK::instance()->wait();
    TP_LOGGING_TASK::instance()->close();
    delete logging_dispatcher_;
    return 0;
}

#include "tpls_export.h"
ACE_FACTORY_DEFINE(TPLS, TP_Logging_Server)
// vim: set et ts=4 sts=4 sw=4:
