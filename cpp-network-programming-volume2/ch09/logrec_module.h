/// \file logrec_module.h
/// \brief The Logrec_Module class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_MODULE_H
#define LOGREC_MODULE_H

#include <ace/Module.h>
#include <ace/Synch_Traits.h>

template<class TASK>
class Logrec_Module: public ACE_Module<ACE_MT_SYNCH>
{
public:
    Logrec_Module(const ACE_TCHAR *name):
        ACE_Module<ACE_MT_SYNCH>(name, &task_, 0, 0,
                                 ACE_Module<ACE_MT_SYNCH>::M_DELETE_READER) {
    }

private:
    TASK task_;
};

#define LOGREC_MODULE(NAME) \
    typedef Logrec_Module<NAME> NAME##_Module

#endif /* !LOGREC_MODULE_H */
// vim: set et ts=4 sts=4 sw=4:
