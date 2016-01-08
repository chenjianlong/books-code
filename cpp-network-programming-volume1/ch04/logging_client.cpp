#include "logging_client.h"
#include <ace/Log_Msg.h>
#include <iostream>

using namespace std;

Logging_Client::~Logging_Client()
{
    logging_peer_.close();
}

int Logging_Client::send(const ACE_Log_Record &log_record)
{
    const size_t max_payload_size =
        4 // type
        + 8 // timestamp
        + 4 // process id
        + 4 // data length
        + ACE_Log_Record::MAXLOGMSGLEN // data
        + ACE_CDR::MAX_ALIGNMENT;

    ACE_OutputCDR payload(max_payload_size);
    payload << log_record;
    ACE_CDR::ULong length = payload.total_length();

    ACE_OutputCDR header(ACE_CDR::MAX_ALIGNMENT + 8);
    header << ACE_OutputCDR::from_boolean(ACE_CDR_BYTE_ORDER);
    header << ACE_CDR::ULong(length);

    iovec iov[2];
    iov[0].iov_base = header.begin()->rd_ptr();
    iov[0].iov_len = 8;
    iov[1].iov_base = payload.begin()->rd_ptr();
    iov[1].iov_len = length;

    return logging_peer_.sendv_n(iov, 2);
}

int main(int argc, char *argv[])
{
    u_short logger_port =
        argc > 1 ? atoi(argv[1]) : 0;
    const char *logger_host =
        argc > 2 ? argv[2] : ACE_DEFAULT_SERVER_HOST;
    int result;

    ACE_INET_Addr server_addr;
    if (logger_port != 0) {
        result = server_addr.set(logger_port, logger_host);
    } else {
        result = server_addr.set("ace_logger", logger_host);
    }

    if (result == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          "lookup %s, %p\n",
                          logger_port == 0 ? "ace_logger": argv[1],
                          logger_host),
                          1);
    }

    ACE_SOCK_Connector connector;
    Logging_Client logging_client;
    if (connector.connect(logging_client.peer(), server_addr) < 0) {
        ACE_ERROR_RETURN((LM_ERROR,
                          "%p\n",
                          "connect()"),
                          1);
    }

    cin.width(ACE_Log_Record::MAXLOGMSGLEN);
    for (;;) {
        string user_input;
        getline(cin, user_input, '\n');
        if (!cin || cin.eof())
            break;

        ACE_Time_Value now(ACE_OS::gettimeofday());
        ACE_Log_Record log_record(LM_INFO, now, ACE_OS::getpid());
        log_record.msg_data(user_input.c_str());
        if (logging_client.send(log_record) == -1) {
            ACE_ERROR_RETURN((LM_ERROR,
                              "%p\n",
                              "logging_client.send()"),
                              1);
        }
    }

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
