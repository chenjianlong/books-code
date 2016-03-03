#include "tss_thread_per_connection_logging_server.h"
#include <ace/TSS_T.h>

class Request_Count {
public:
    Request_Count(): count_(0) {
    }

    void increment() {
        ++count_;
    }

    int value() const {
        return count_;
    };

private:
    int count_;
};

static ACE_TSS<Request_Count> request_count;

int TSS_Thread_Per_Connection_Logging_Server::handle_data(ACE_SOCK_Stream *client) {
    ACE_FILE_IO log_file;
    make_log_file(log_file, client);

    client->disable(ACE_NONBLOCK);

    Logging_Handler logging_handler(log_file, *client);
    ACE_Thread_Manager *tm = ACE_Thread_Manager::instance();
    ACE_thread_t me = ACE_OS::thr_self();

    while (!tm->testcancel(me) && logging_handler.log_record() != -1) {
        request_count->increment();
    }

    log_file.close();
    ACE_DEBUG((LM_DEBUG, "request_count = %d\n", request_count->value()));
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
