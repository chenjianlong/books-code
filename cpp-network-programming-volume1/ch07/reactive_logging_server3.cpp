#include "reactive_logging_server.h"

int Reactive_Logging_Server::open(u_short logger_port)
{
    Iterative_Logging_Server::open(logger_port);
    master_handle_set_.set_bit(acceptor().get_handle());
    acceptor().enable(ACE_NONBLOCK);
    return 0;
}

int Reactive_Logging_Server::wait_for_multiple_events()
{
    active_handlers_ = master_handle_set_;
    int width = int(active_handlers_.max_set() + 1);
    return ACE::select(width, active_handlers_);
}

int Reactive_Logging_Server::handle_connections()
{
    if (active_handlers_.is_set(acceptor().get_handle())) {
        while (acceptor().accept(logging_handler().peer()) == 0) {
            master_handle_set_.set_bit(logging_handler().peer().get_handle());
            active_handlers_.clr_bit(acceptor().get_handle());
        }
    }

    return 0;
}

int Reactive_Logging_Server::handle_data(ACE_SOCK_Stream*)
{
    ACE_Handle_Set_Iterator peer_iterator(active_handlers_);
    for (ACE_HANDLE handle;
            (handle = peer_iterator()) != ACE_INVALID_HANDLE;) {
        logging_handler().peer().set_handle(handle);
        if (logging_handler().log_record() == -1) {
            master_handle_set_.clr_bit(handle);
            logging_handler().close();
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    Reactive_Logging_Server server;
    if (server.run(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "server.run()"), 1);

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
