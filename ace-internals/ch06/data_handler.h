/// \file data_handler.h
/// \brief The Data_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-04-13

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <ace/Asynch_IO.h>
#include <ace/Message_Block.h>

class Data_Handler: public ACE_Service_Handler
{
public:
    virtual void open(ACE_HANDLE handle, ACE_Message_Block&);

    virtual void handle_read_stream(
        const ACE_Asynch_Read_Stream::Result &result);

    int initiate_read_stream();
    int initiate_write_stream(ACE_Message_Block &mb, size_t nbytes);

private:
    ACE_Asynch_Read_Stream rs_;
    ACE_Asynch_Write_Stream ws_;
    ACE_HANDLE handle_;
    ACE_SYNCH_MUTEX lock_;
    int io_count_;
    int flg_cancel_;
    size_t total_snd_;
    size_t total_rcv_;
    int total_w_;
    int total_r_;
};

#endif /* !DATA_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
