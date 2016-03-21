/// \file logrec_reader_module.h
/// \brief The Logrec_Reader_Module class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_READER_MODULE_H
#define LOGREC_READER_MODULE_H

#include "logrec_reader.h"
#include <ace/Module.h>

class Logrec_Reader_Module: public ACE_Module<ACE_MT_SYNCH>
{
public:
    Logrec_Reader_Module(const ACE_TString &filename):
        ACE_Module<ACE_MT_SYNCH>("Logrec Reader", &task_, 0, 0,
                                 ACE_Module<ACE_MT_SYNCH>::M_DELETE_READER),
        task_(filename) {
    }

private:
    // Converts the logfile into chains of message blocks.
    Logrec_Reader task_;
};

#endif /* !LOGREC_READER_MODULE_H */
// vim: set et ts=4 sts=4 sw=4:
