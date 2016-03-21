/// \file logrec_reader.h
/// \brief The Logrec_Reader class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_READER_H
#define LOGREC_READER_H

#include <ace/Task.h>
#include <ace/FILE_IO.h>

class Logrec_Reader: public ACE_Task<ACE_MT_SYNCH>
{
public:
    enum { MB_CLIENT = ACE_Message_Block::MB_USER, MB_TYPE, MB_PID, MB_TIME, MB_TEXT };

    Logrec_Reader(const ACE_TString &file): filename_(file) {
    }

    virtual int open(void*);
    virtual int svc();

private:
    ACE_TString filename_;
    ACE_FILE_IO logfile_;
};

#endif /* !LOGREC_READER_H */
// vim: set et ts=4 sts=4 sw=4:
