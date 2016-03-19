#include "ac_client_logging_daemon.h"
#include <ace/OS_NS_string.h>
#include <ace/Get_Opt.h>

int AC_Client_Logging_Daemon::init(int argc, ACE_TCHAR *argv[])
{
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

    ACE_INET_Addr cld_addr(cld_port);
    ACE_INET_Addr sld_addr(sld_port, sld_host);
    if (acceptor_.open(cld_addr) == -1) return -1;
    AC_Output_Handler *oh = &output_handler_;
    if (connector_.connect(oh, sld_addr) == -1) {
        acceptor_.close();
        return -1;
    }

    return 0;
}

int AC_Client_Logging_Daemon::fini()
{
    return acceptor_.close();
}

#include "ac_cld_export.h"

ACE_FACTORY_DEFINE(AC_CLD, AC_Client_Logging_Daemon)
// vim: set et ts=4 sts=4 sw=4:
