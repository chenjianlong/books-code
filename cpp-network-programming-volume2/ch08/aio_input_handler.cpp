#include "aio_input_handler.h"
#include "aio_output_handler.h"
#include "aio_cld_acceptor.h"
#include <ace/CDR_Stream.h>
#include <iostream>

using namespace std;

AIO_Input_Handler::~AIO_Input_Handler()
{
    reader_.cancel();
    ACE_OS::closesocket(handle());
    if (mblk_ != 0)
        mblk_->release();

    mblk_ = 0;
    acceptor_->remove(this);
}

void AIO_Input_Handler::open(ACE_HANDLE new_handle, ACE_Message_Block&)
{
    cout << "AIO_Input_Handler::open" << endl;
    reader_.open(*this, new_handle, 0, proactor());
    ACE_NEW_NORETURN(mblk_, ACE_Message_Block(ACE_DEFAULT_CDR_BUFSIZE));
    ACE_CDR::mb_align(mblk_);
    reader_.read(*mblk_, LOG_HEADER_SIZE);
}

void AIO_Input_Handler::handle_read_stream(
    const ACE_Asynch_Read_Stream::Result &result)
{
    cout << "AIO_Input_Handler::handle_read_stream" << endl;
    if (!result.success() || result.bytes_transferred() == 0) {
        delete this;
    } else if (result.bytes_transferred() < result.bytes_to_read()) {
        reader_.read(*mblk_,
                     result.bytes_to_read() - result.bytes_transferred());
    } else if (mblk_->length() == LOG_HEADER_SIZE) {
        ACE_InputCDR cdr(mblk_);
        ACE_CDR::Boolean byte_order;
        cdr >> ACE_InputCDR::to_boolean(byte_order);
        cdr.reset_byte_order(byte_order);

        ACE_CDR::ULong length;
        cdr >> length;

        mblk_->size(length + LOG_HEADER_SIZE);
        reader_.read(*mblk_, length);
    } else {
        if (OUTPUT_HANDLER::instance()->put(mblk_) == -1) {
            mblk_->release();
        }

        ACE_NEW_NORETURN(mblk_, ACE_Message_Block(ACE_DEFAULT_CDR_BUFSIZE));
        ACE_CDR::mb_align(mblk_);
        reader_.read(*mblk_, LOG_HEADER_SIZE);
    }
}
// vim: set et ts=4 sts=4 sw=4:
