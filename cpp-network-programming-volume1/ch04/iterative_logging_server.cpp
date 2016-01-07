#include "iterative_logging_server.h"

Iterative_Logging_Server::Iterative_Logging_Server():
    logging_handler_(log_file_)
{
}

Iterative_Logging_Server::~Iterative_Logging_Server()
{
    log_file_.close();
}

int Iterative_Logging_Server::open(u_short logger_port)
{
    if (make_log_file(log_file_) == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          "%p\n",
                          "make_log_file()"),
                          -1);
    }

    return Logging_Server::open(logger_port);
}

int Iterative_Logging_Server::handle_connections()
{
    ACE_INET_Addr logging_peer_addr;
    if (acceptor().accept(logging_handler_.peer(),
                          &logging_peer_addr) == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          "%p\n",
                          "accept()"),
                          -1);
    }

    ACE_DEBUG((LM_DEBUG,
        "Accepted connection from %s\n", logging_peer_addr.get_host_name()));
    return 0;
}

int Iterative_Logging_Server::handle_data(ACE_SOCK_Stream*) {
    while (logging_handler_.log_record() != -1) {
        continue;
    }

    logging_handler_.close();
    return 0;
}

int main(int argc, char *argv[])
{
    Iterative_Logging_Server server;

    if (server.run(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR,
                          "%p\n",
                          "server.run()"),
                          -1);

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
