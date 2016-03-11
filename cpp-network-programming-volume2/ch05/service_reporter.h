/// \file service_reporter.h
/// \brief The Service_Reporter class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-09

#ifndef SERVICE_REPORTER_H
#define SERVICE_REPORTER_H

#include <ace/Service_Object.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>

class Service_Reporter: public ACE_Service_Object
{
public:
    Service_Reporter(ACE_Reactor *r = ACE_Reactor::instance()):
        ACE_Service_Object(r) {
    }

    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();
    virtual int info(ACE_TCHAR **, size_t) const;
    virtual int suspend();
    virtual int resume();

protected:
    virtual int handle_input(ACE_HANDLE);
    virtual ACE_HANDLE get_handle() const {
        return acceptor_.get_handle();
    }

private:
    ACE_SOCK_Acceptor acceptor_;
    enum { DEFAULT_PORT = 9411 };
};

#endif /* !SERVICE_REPORTER_H */
// vim: set et ts=4 sts=4 sw=4:
