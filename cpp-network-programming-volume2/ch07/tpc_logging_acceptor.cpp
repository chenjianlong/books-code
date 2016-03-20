#include "tpc_logging_acceptor.h"
#include "reactor_logging_server_adapter.h"
#include "tpcls_export.h"
#include <ace/OS.h>

int TPC_Logging_Acceptor::open(const ACE_SOCK_Acceptor::PEER_ADDR &local_addr,
                               ACE_Reactor *reactor,
                               int flags, int use_select, int reuse_addr)
{
    return PARENT::open(local_addr, reactor, flags, use_select, reuse_addr);
}

int TPC_Logging_Acceptor::accept_svc_handler(TPC_Logging_Handler *sh)
{
    return PARENT::accept_svc_handler(sh);
}

int TPC_Logging_Acceptor::handle_close(ACE_HANDLE h, ACE_Reactor_Mask mask)
{
    PARENT::handle_close(h, mask);
    delete this;
    return 0;
}

typedef Reactor_Logging_Server_Adapter<TPC_Logging_Acceptor> TPC_Logging_Server;

ACE_FACTORY_DEFINE(TPCLS, TPC_Logging_Server)
// vim: set et ts=4 sts=4 sw=4:
