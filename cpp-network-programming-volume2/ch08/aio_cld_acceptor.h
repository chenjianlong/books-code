/// \file aio_cld_acceptor.h
/// \brief The AIO_CLD_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef AIO_CLD_ACCEPTOR_H
#define AIO_CLD_ACCEPTOR_H

#include "aio_input_handler.h"
#include <ace/Asynch_Acceptor.h>
#include <ace/Unbounded_Set.h>

class AIO_CLD_Acceptor: public ACE_Asynch_Acceptor<AIO_Input_Handler>
{
public:
    void close();

    void remove(AIO_Input_Handler *ih) {
        clients_.remove(ih);
    }

protected:
    virtual AIO_Input_Handler *make_handler();
    ACE_Unbounded_Set<AIO_Input_Handler*> clients_;
};

#endif /* !AIO_CLD_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
