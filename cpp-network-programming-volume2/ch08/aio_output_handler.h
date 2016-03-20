/// \file aio_output_handler.h
/// \brief The AIO_Output_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef AIO_OUTPUT_HANDLER_H
#define AIO_OUTPUT_HANDLER_H

#include <ace/Task.h>
#include <ace/Asynch_IO.h>

class AIO_Output_Handler:
    public ACE_Task<ACE_NULL_SYNCH>, public ACE_Service_Handler
{
public:
    AIO_Output_Handler(): can_write_(0) {
    }

    virtual ~AIO_Output_Handler() {
    }

    virtual int put(ACE_Message_Block*, ACE_Time_Value* = 0);
    virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

protected:
    void start_write(ACE_Message_Block *mblk = 0);
    void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);
    void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);

protected:
    ACE_Asynch_Read_Stream reader_;
    ACE_Asynch_Write_Stream writer_;
    int can_write_;
};

typedef ACE_Unmanaged_Singleton<AIO_Output_Handler, ACE_Null_Mutex> OUTPUT_HANDLER;

#endif /* !AIO_OUTPUT_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
