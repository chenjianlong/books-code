#include "tpc_logging_acceptor.h"
#include "reactor_logging_server_adapter.h"
#include "tpcls_export.h"
#include <ace/OS.h>
#include <iostream>

using namespace std;

#ifndef TPC_CERTIFICATE_FILENAME
#   define TPC_CERTIFICATE_FILENAME "tpc-cert.pem"
#endif /* TPC_CERTIFICATE_FILENAME */

#ifndef TPC_KEY_FILENAME
#   define TPC_KEY_FILENAME "tpc-key.pem"
#endif /* TPC_KEY_FILENAME */

int TPC_Logging_Acceptor::open(const ACE_SOCK_Acceptor::PEER_ADDR &local_addr,
                               ACE_Reactor *reactor,
                               int flags, int use_select, int reuse_addr)
{
    if (PARENT::open(local_addr, reactor, flags, use_select, reuse_addr) != 0)
        return -1;

    OpenSSL_add_ssl_algorithms();
    ssl_ctx_ = SSL_CTX_new(SSLv3_server_method());
    if (ssl_ctx_ == 0)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_new, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    if (SSL_CTX_use_certificate_file(ssl_ctx_,
                                     TPC_CERTIFICATE_FILENAME,
                                     SSL_FILETYPE_PEM) <= 0)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_use_certificate_file"
                          ", errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    if (SSL_CTX_use_PrivateKey_file(ssl_ctx_,
                                    TPC_KEY_FILENAME,
                                    SSL_FILETYPE_PEM) <= 0)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_use_certificate_file"
                          ", errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    if (!SSL_CTX_check_private_key(ssl_ctx_))
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_check_private_key, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    ssl_ = SSL_new(ssl_ctx_);
    return ssl_ == 0 ? -1 : 0;
}

int TPC_Logging_Acceptor::accept_svc_handler(TPC_Logging_Handler *sh)
{
    if (PARENT::accept_svc_handler(sh) == -1) {
        cout << "TPC_Logging_Acceptor::accept_svc_handler failed" << endl;
        return -1;
    }

    SSL_clear(ssl_);
    SSL_set_fd(ssl_, reinterpret_cast<int>(sh->get_handle()));
    SSL_set_verify(ssl_, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, 0);
    if (SSL_accept(ssl_) == -1)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_accept, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    if (SSL_shutdown(ssl_) == -1)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_shutdown, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    cout << "TPC_Logging_Acceptor::accept_svc_handler success" << endl;
    return 0;
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
