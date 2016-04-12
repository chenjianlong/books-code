#include <ace/Task.h>
#include <ace/Synch_Traits.h>
#include <ace/OS_NS_stdio.h>
#include <ace/OS_NS_unistd.h>

class Counting_Test_Producer: public ACE_Task<ACE_MT_SYNCH>
{
public:
    Counting_Test_Producer(ACE_Message_Queue<ACE_MT_SYNCH> *queue):
        ACE_Task<ACE_MT_SYNCH>(0, queue) {
    }

    virtual int svc(void);
};

int Counting_Test_Producer::svc(void)
{
    const int MAX_MESSAGES = 30;
    int produced = 0;
    char data[256] = { 0 };
    ACE_Message_Block *b = 0;

    while (true) {
        ACE_OS::sprintf(data, "%s--%d", "test_message", produced);

        ACE_NEW_NORETURN(b, ACE_Message_Block(256));
        if (b == 0) {
            break;
        }

        b->copy(data, 256);
        if (produced >= MAX_MESSAGES) {
            b->msg_type(ACE_Message_Block::MB_STOP);
            if (this->putq(b) == -1) {
                b->release();
                break;
            }

            produced++;
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("Producer put the data: %s.\n"), b->base()));
            break;
        }

        if (this->putq(b) == -1) {
            b->release();
            break;
        }

        produced++;
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("Producer put the data: %s.\n"), b->base()));
        ACE_OS::sleep(1);
    }

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("Producer done\n")));
    return 0;
}

class Counting_Test_Consumer: public ACE_Task<ACE_MT_SYNCH>
{
public:
    Counting_Test_Consumer(ACE_Message_Queue<ACE_MT_SYNCH> *queue):
        ACE_Task<ACE_MT_SYNCH>(0, queue) {
    }

    virtual int svc(void);
};

int Counting_Test_Consumer::svc(void)
{
    int consumer = 0;
    ACE_Message_Block *b = 0;
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("in consumer svc.\n")));
    ACE_OS::sleep(30);
    while (true) {
        if (this->getq(b) == -1) {
            break;
        }

        if (b->msg_type() == ACE_Message_Block::MB_STOP) {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("Consumer get the data: %s.\n"), b->base()));
            b->release();
            consumer++;
            break;
        }

        ACE_DEBUG((LM_DEBUG, ACE_TEXT("Consumer get the data: %s.\n"), b->base()));
        b->release();
        consumer++;
        ACE_OS::sleep(5);
    }

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("Consumer done\n")));
    return 0;
}

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    ACE_Message_Queue<ACE_MT_SYNCH> queue(2 * 1024 * 1024);

    Counting_Test_Producer producer(&queue);
    Counting_Test_Consumer consumer(&queue);

    if (consumer.activate(THR_NEW_LWP | THR_DETACHED | THR_INHERIT_SCHED, 1) == -1) {
        ACE_ERROR((LM_ERROR, ACE_TEXT("Consumers %p\n"), ACE_TEXT("activate")));
        return -1;
    }

    if (producer.activate(THR_NEW_LWP | THR_DETACHED | THR_INHERIT_SCHED, 1) == -1) {
        ACE_ERROR((LM_ERROR, ACE_TEXT("Producers %p\n"), ACE_TEXT("activate")));
        consumer.wait();
        return -1;
    }

    ACE_Thread_Manager::instance()->wait();
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("Ending test!\n")));
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
