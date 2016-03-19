#include "ac_cld_connector.h"
#include <iostream>

#ifndef CLD_CERTIFICATE_FILENAME
#   define CLD_CERTIFICATE_FILENAME "cld-cert.pem"
#endif /* !CLD_CERTIFICATE_FILENAME */

#ifndef CLD_KEY_FILENAME
#   define CLD_KEY_FILENAME "cld-key.pem"
#endif /* !CLD_KEY_FILENAME */

using namespace std;

int AC_CLD_Connector::open(ACE_Reactor *r, int flags)
{
    if (PARENT::open(r, flags) != 0) return -1;
    OpenSSL_add_ssl_algorithms();
    ssl_ctx_ = SSL_CTX_new(SSLv3_client_method());
    if (ssl_ctx_ == 0) return -1;

    if (SSL_CTX_use_certificate_file(ssl_ctx_, CLD_CERTIFICATE_FILENAME, SSL_FILETYPE_PEM) <= 0)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_use_certificate_file, errno=%d,%m",
                          ACE_OS::last_error()),
                          -1);

    if (SSL_CTX_use_PrivateKey_file(ssl_ctx_, CLD_KEY_FILENAME, SSL_FILETYPE_PEM) <= 0)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_use_PrivateKey_file, errno=%d,%m",
                          ACE_OS::last_error()),
                          -1);

    if (!SSL_CTX_check_private_key(ssl_ctx_))
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_CTX_check_private_key, errno=%d,%m",
                          ACE_OS::last_error()),
                          -1);

    ssl_ = SSL_new(ssl_ctx_);
    return ssl_ == 0 ? -1 : 0;
}

int AC_CLD_Connector::connect_svc_handler(AC_Output_Handler *svc_handler,
                                          const ACE_SOCK_Connector::PEER_ADDR &remote_addr,
                                          ACE_Time_Value *timeout,
                                          const ACE_SOCK_Connector::PEER_ADDR &local_addr,
                                          int reuse_addr, int flags, int perms)
{
    if (PARENT::connect_svc_handler(svc_handler, remote_addr,
                                    timeout, local_addr,
                                    reuse_addr, flags, perms) == -1)
        return -1;

    SSL_clear(ssl_);
    SSL_set_fd(ssl_, reinterpret_cast<int>(svc_handler->get_handle()));
    SSL_set_verify(ssl_, SSL_VERIFY_PEER, 0);
    if (SSL_connect(ssl_) == -1)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_connect, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    if (SSL_shutdown(ssl_) == -1)
        ACE_ERROR_RETURN((LM_ERROR,
                          "Failed to SSL_shutdown, errno=%d,%m\n",
                          ACE_OS::last_error()),
                          -1);

    remote_addr_ = remote_addr;
    return 0;
}

int AC_CLD_Connector::reconnect()
{
    const size_t MAX_RETRIES = 5;
    ACE_Time_Value timeout(1);
    size_t i;
    for (i = 0; i < MAX_RETRIES; ++i) {
        ACE_Synch_Options options(ACE_Synch_Options::USE_TIMEOUT, timeout);
        if (i > 0) ACE_OS::sleep(timeout);
        if (connect(handler_, remote_addr_, options) == 0)
            break;

        timeout *= 2;
    }

    return i == MAX_RETRIES ? -1 : 0;
}
// vim: set et ts=4 sts=4 sw=4:

