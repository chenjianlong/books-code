#include "tpc_logging_handler.h"
#include <ace/OS_NS_string.h>
#include <ace/FILE_Connector.h>

int TPC_Logging_Handler::open(void*)
{
    static const ACE_TCHAR LOGFILE_SUFFIX[] = ACE_TEXT(".log");
    ACE_TCHAR filename[MAXHOSTNAMELEN + sizeof(LOGFILE_SUFFIX)];
    ACE_INET_Addr logging_peer_addr;

    peer_.get_remote_addr(logging_peer_addr);
    logging_peer_addr.get_host_name(filename, MAXHOSTNAMELEN);
    ACE_OS::strcat(filename, LOGFILE_SUFFIX);

    ACE_FILE_Connector connector;
    connector.connect(log_file_,
                      ACE_FILE_Addr(filename),
                      0, // No timeout
                      ACE_Addr::sap_any, // Ignored
                      0, // Dno't try to reuse the addr.
                      O_RDWR | O_CREAT | O_APPEND,
                      ACE_DEFAULT_FILE_PERMS);

    logging_handler_.peer().set_handle(peer().get_handle());
    return activate(THR_NEW_LWP | THR_DETACHED);
}

int TPC_Logging_Handler::svc()
{
    for (;;) {
        switch (logging_handler_.log_record()) {
            case -1: return -1; // Error.
            default: continue;  // Default case.
        }
    }

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
