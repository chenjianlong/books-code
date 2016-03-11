#include "reactor_logging_server_adapter.h"
#include "logging_acceptor.h"
#include "sld_export.h"

typedef Reactor_Logging_Server_Adapter<Logging_Acceptor> Server_Logging_Daemon;

ACE_FACTORY_DEFINE(SLD, Server_Logging_Daemon)
// vim: set et ts=4 sts=4 sw=4:
