#include "reactor_logging_server_adapter.h"
#include "logging_acceptor_ex.h"
#include "sldex_export.h"

typedef Reactor_Logging_Server_Adapter<Logging_Acceptor_Ex> Server_Logging_Daemon_Ex;

ACE_FACTORY_DEFINE(SLDEX, Server_Logging_Daemon_Ex)
// vim: set et ts=4 sts=4 sw=4:
