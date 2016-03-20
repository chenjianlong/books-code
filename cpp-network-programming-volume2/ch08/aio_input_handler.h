/// \file aio_input_handler.h
/// \brief The AIO_Input_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef AIO_INPUT_HANDLER_H
#define AIO_INPUT_HANDLER_H

#include <ace/Asynch_IO.h>

class AIO_CLD_Acceptor;

class AIO_Input_Handler: public ACE_Service_Handler
{
public:
    AIO_Input_Handler(AIO_CLD_Acceptor *acc = 0):
        acceptor_(acc), mblk_(0) {
    }

    virtual ~AIO_Input_Handler();

    virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

protected:
    virtual void handle_read_stream(
        const ACE_Asynch_Read_Stream::Result &result);

protected:
    enum { LOG_HEADER_SIZE = 8 };
    AIO_CLD_Acceptor *acceptor_;
    ACE_Message_Block *mblk_;
    ACE_Asynch_Read_Stream reader_;
};

#endif /* !AIO_INPUT_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
