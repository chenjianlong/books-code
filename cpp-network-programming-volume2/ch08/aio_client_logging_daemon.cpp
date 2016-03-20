#include "aio_client_logging_daemon.h"
#include "aio_cld_connector.h"
#include <ace/Proactor.h>
#include <ace/OS_NS_string.h>
#include <ace/Get_Opt.h>
#include <iostream>

using namespace std;

int AIO_Client_Logging_Daemon::init(int argc, ACE_TCHAR *argv[])
{
    cout << "AIO_Client_Logging_Daemon::init" << endl;
    u_short cld_port = ACE_DEFAULT_SERVICE_PORT;
    u_short sld_port = ACE_DEFAULT_LOGGING_SERVER_PORT;
    ACE_TCHAR sld_host[MAXHOSTNAMELEN];
    ACE_OS::strcpy(sld_host, ACE_LOCALHOST);
    ACE_Get_Opt get_opt(argc, argv, ACE_TEXT("p:r:s:"), 0);
    get_opt.long_option(ACE_TEXT("client_port"), 'p', ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT("server_port"), 'r', ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT("server_name"), 's', ACE_Get_Opt::ARG_REQUIRED);

    for (int c; (c = get_opt()) != -1;) {
        switch (c) {
            case 'p':
                cld_port = static_cast<u_short>(ACE_OS::atoi(get_opt.opt_arg()));
                break;
            case 'r':
                sld_port = static_cast<u_short>(ACE_OS::atoi(get_opt.opt_arg()));
                break;
            case 's':
                ACE_OS::strsncpy(sld_host, get_opt.opt_arg(), MAXHOSTNAMELEN);
                break;
        }
    }

    cld_addr_.set(cld_port);
    sld_addr_.set(sld_port, sld_host);
    return activate(THR_SCOPE_SYSTEM);
}

int AIO_Client_Logging_Daemon::fini()
{
    cout << "AIO_Client_Logging_Daemon::fini" << endl;
    ACE_Proactor::instance()->proactor_end_event_loop();
    wait();
    return 0;
}

int AIO_Client_Logging_Daemon::svc()
{
    cout << "AIO_Client_Logging_Daemon::svc" << endl;
    if (acceptor_.open(cld_addr_) == -1) {
        cout << "Failed to open acceptor" << endl;
        return -1;
    }

    if (CLD_CONNECTOR::instance()->connect(sld_addr_) == 0) {
        cout << "before proactor_run_event_loop" << endl;
        ACE_Proactor::instance()->proactor_run_event_loop();
        cout << "after proactor_run_event_loop" << endl;
    }

    acceptor_.close();
    CLD_CONNECTOR::close();
    OUTPUT_HANDLER::close();
    return 0;
}

#include "aio_cld_export.h"
ACE_FACTORY_DEFINE(AIO_CLD, AIO_Client_Logging_Daemon)
// vim: set et ts=4 sts=4 sw=4:
