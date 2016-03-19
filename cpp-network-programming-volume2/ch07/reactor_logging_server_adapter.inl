template<class ACCEPTOR>
int Reactor_Logging_Server_Adapter<ACCEPTOR>::init(int argc, ACE_TCHAR *argv[])
{
    int i;
    char **array = 0;
    ACE_NEW_RETURN(array, char*[argc], -1);
    ACE_Auto_Array_Ptr<char*> char_argv(array);

    for (i = 0; i < argc; ++i)
        char_argv[i] = ACE::strnew(ACE_TEXT_ALWAYS_CHAR(argv[i]));

    ACE_NEW_NORETURN(server_,
        Reactor_Logging_Server<ACCEPTOR>(i,
                                         char_argv.get(),
                                         ACE_Reactor::instance()));

    for (i = 0; i < argc; ++i)
        ACE::strdelete(char_argv[i]);
    return server_ == 0 ? -1 : 0;
}

template<class ACCEPTOR>
int Reactor_Logging_Server_Adapter<ACCEPTOR>::fini()
{
    if (!server_)
        return -1;

    // Don't need to call handle_close, it will called on ACE_Reactor::close_instance()
    // server_->handle_close();
    server_ = 0;
    return 0;
}

template<class ACCEPTOR>
int Reactor_Logging_Server_Adapter<ACCEPTOR>::info(
    ACE_TCHAR **bufferp, size_t length) const
{
    if (!server_)
        return -1;

    typename ACCEPTOR::PEER_ADDR local_addr;
    server_->acceptor().get_local_addr(local_addr);

    ACE_TCHAR buf[BUFSIZ];
    ACE_OS::sprintf(buf, ACE_TEXT("%hu"), local_addr.get_port_number());
    strcat(buf, ACE_TEXT("/tcp # Reactive logging server\n"));
    if (*bufferp == 0) *bufferp = ACE::strnew(buf);
    else strncpy(*bufferp, buf, length);
    return strlen(*bufferp);
}

template<class ACCEPTOR>
int Reactor_Logging_Server_Adapter<ACCEPTOR>::suspend()
{
    if (!server_)
        return -1;

    return server_->reactor()->suspend_handler(server_);
}

template<class ACCEPTOR>
int Reactor_Logging_Server_Adapter<ACCEPTOR>::resume()
{
    if (!server_)
        return -1;

    return server_->reactor()->resume_handler(server_);
}
// vim: set et ts=4 sts=4 sw=4:
