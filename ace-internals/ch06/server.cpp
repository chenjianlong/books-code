#include "data_handler.h"
#include <ace/Asynch_Acceptor.h>
#include <ace/Proactor.h>
#include <ace/OS_Memory.h>
#include <iostream>

using namespace std;

class Acceptor: public ACE_Asynch_Acceptor<Data_Handler>
{
public:
    Data_Handler *make_hanlder() {
        Data_Handler *h;
        ACE_NEW_RETURN(h, Data_Handler(), 0);
        return h;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    ACE_INET_Addr addr(atoi(argv[1]));

    cout << "Listen to port " << argv[1] << endl;
    Acceptor acceptor;
    if (acceptor.open(addr) == -1) {
        cerr << "Failed to open" << endl;
        return 1;
    }

    ACE_Proactor::instance()->proactor_run_event_loop();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
