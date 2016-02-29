#include "reactive_logging_server4.h"

int Reactive_Logging_Server_Ex::open(u_short logger_port)
{
    Logging_Server::open(logger_port);
    master_handle_set_.set_bit(acceptor().get_handle());
    acceptor().enable(ACE_NONBLOCK);
    return 0;
}

int Reactive_Logging_Server_Ex::wait_for_multiple_events()
{
    active_read_handlers_ = master_handle_set_;
    int width = int(active_read_handlers_.max_set() + 1);
    return ACE::select(width, active_read_handlers_);
}

int Reactive_Logging_Server_Ex::handle_connections()
{
    ACE_SOCK_Stream logging_peer;

    while (acceptor().accept(logging_peer) != -1) {
        ACE_FILE_IO *log_file = new ACE_FILE_IO;

        make_log_file(*log_file, &logging_peer);

        log_map_.bind(logging_peer.get_handle(), log_file);
        master_handle_set_.set_bit(logging_peer.get_handle());
        active_read_handlers_.clr_bit(acceptor().get_handle());
    }

    return 0;
}

int Reactive_Logging_Server_Ex::handle_data(ACE_SOCK_Stream*)
{
    ACE_Handle_Set_Iterator peer_iterator(active_read_handlers_);
    for (ACE_HANDLE handle;
            (handle = peer_iterator()) != ACE_INVALID_HANDLE;) {
        ACE_FILE_IO *log_file;
        log_map_.find(handle, log_file);

        Logging_Handler logging_handler(*log_file, handle);
        if (logging_handler.log_record() == -1) {
            logging_handler.close();
            master_handle_set_.clr_bit(handle);
            log_map_.unbind(handle);
            log_file->close();
            delete log_file;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    Reactive_Logging_Server_Ex server;
    if (server.run(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "server.run()"), 1);

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
