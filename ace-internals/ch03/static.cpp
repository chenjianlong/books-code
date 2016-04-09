#include <ace/Service_Object.h>
#include <ace/Service_Config.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>

class StaticObj: public ACE_Service_Object
{
public:
    StaticObj() {}
    virtual ~StaticObj() {}

    virtual int init(int, ACE_TCHAR **) {
        ACE_DEBUG((LM_DEBUG, "This StaticObj::init------\n"));
        return 0;
    }

    virtual int suspend() {
        ACE_DEBUG((LM_DEBUG, "This StaticObj::suspend------\n"));
        return 0;
    }

    virtual int resume() {
        ACE_DEBUG((LM_DEBUG, "This StaticObj::resume------\n"));
        return 0;
    }

    virtual int fini() {
        ACE_DEBUG((LM_DEBUG, "This StaticObj::fini------\n"));
        return 0;
    }
};

ACE_FACTORY_DEFINE(ACE, StaticObj);

ACE_STATIC_SVC_DEFINE(StaticObj_Discriptor,
                      ACE_TEXT("StaticObj"),
                      ACE_SVC_OBJ_T,
                      &ACE_SVC_NAME(StaticObj),
                      ACE_Service_Type::DELETE_THIS | ACE_Service_Type::DELETE_OBJ,
                      1)

ACE_STATIC_SVC_REQUIRE(StaticObj_Discriptor)

int main(int argc, char *argv[])
{
    if (ACE_Service_Config::open(argc, argv, ACE_DEFAULT_LOGGER_KEY, 0) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "ACE_Service_Config::open"), -1);

    return ACE_Reactor::run_event_loop();
}
// vim: set et ts=4 sts=4 sw=4:
