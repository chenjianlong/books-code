#include "aio_cld_acceptor.h"
#include "aio_input_handler.h"
#include <iostream>

using namespace std;

AIO_Input_Handler* AIO_CLD_Acceptor::make_handler()
{
    cout << "AIO_CLD_Acceptor::make_handler" << endl;
    AIO_Input_Handler *ih;
    ACE_NEW_RETURN(ih, AIO_Input_Handler(this), 0);
    if (clients_.insert(ih) == -1) {
        cout << "Failed to insert input handler" << endl;
        delete ih;
        return 0;
    }

    return ih;
}

void AIO_CLD_Acceptor::close()
{
    ACE_Unbounded_Set_Iterator<AIO_Input_Handler*> iter(clients_.begin());
    AIO_Input_Handler **ih;
    while (iter.next(ih)) delete *ih;
}

// vim: set et ts=4 sts=4 sw=4:
