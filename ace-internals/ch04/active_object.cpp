#include <ace/Log_Msg.h>
#include <ace/OS_NS_unistd.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h>
#include <ace/Future.h>
#include <ace/Task.h>
#include <ace/Thread_Manager.h>

class Servant
{
public:
    Servant() {
        status_result_ = 1;
    }

    int status_update(void) {
        ACE_DEBUG((LM_DEBUG,
                   "Obtaining a status_update in %t"
                   " thread of control\n"));
        ACE_OS::sleep(2);
        return next_result_id();
    }

private:
    int next_result_id(void) {
        return status_result_++;
    }

    int status_result_;
};

class StatusUpdate: public ACE_Method_Request
{
public:
    StatusUpdate(Servant &controller, ACE_Future<int> &returnVal):
            controller_(controller), returnVal_(returnVal) {
        ACE_DEBUG((LM_DEBUG, "StatusUpdate::StatusUpdate.\n"));
    }

    virtual int call(void) {
        ACE_DEBUG((LM_DEBUG, "StatusUpdate::call.\n"));
        this->returnVal_.set(this->controller_.status_update());
        return 0;
    }

private:
    Servant &controller_;
    ACE_Future<int> returnVal_;
};

class ExitMethod: public ACE_Method_Request
{
public:
    virtual int call(void) {
        return -1;
    }
};

class Scheduler: public ACE_Task_Base
{
public:
    Scheduler() {
        ACE_DEBUG((LM_DEBUG, "Scheduler::Scheduler.\n"));
        this->activate();
    }

    virtual int svc(void) {
        ACE_DEBUG((LM_DEBUG, "Scheduler::svc.\n"));
        while (true) {
            ACE_Auto_Ptr<ACE_Method_Request> request(this->activation_queue_.dequeue());
            if (request->call() == -1) {
                break;
            }
        }

        return 0;
    }

    int enqueue(ACE_Method_Request *request) {
        ACE_DEBUG((LM_DEBUG, "Scheduler::enqueue.\n"));
        return this->activation_queue_.enqueue(request);
    }

private:
    ACE_Activation_Queue activation_queue_;
};

class Proxy
{
public:
    ACE_Future<int> status_update(void) {
        ACE_DEBUG((LM_DEBUG, "Proxy::status_update.\n"));
        ACE_Future<int> result;
        this->scheduler_.enqueue(new StatusUpdate(this->controller_, result));
        return result;
    }

    void exit(void) {
        ACE_DEBUG((LM_DEBUG, "Proxy::exit.\n"));
        this->scheduler_.enqueue(new ExitMethod);
    }

private:
    Scheduler scheduler_;
    Servant controller_;
};

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    Proxy controller;
    ACE_Future<int> results[10];
    for (int i = 0; i < 10; ++i)
        results[i] = controller.status_update();

    ACE_OS::sleep(5);
    for (int j = 0; j < 10; ++j) {
        int result = 0;
        results[j].get(result);
        ACE_DEBUG((LM_DEBUG, "New status_update %d\n", result));
    }

    controller.exit();
    ACE_Thread_Manager::instance()->wait();
    return 0;

}
// vim: set et ts=4 sts=4 sw=4:
