#include "logrec_writer.h"
#include "logrec_separator.h"
#include "logrec_formatter.h"
#include "logrec_reader_module.h"
#include <ace/Log_Msg.h>
#include <ace/Stream.h>
#include <ace/Thread_Manager.h>

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    if (argc != 2)
        ACE_ERROR_RETURN((LM_ERROR,
                          "usage: %s logfile\n", argv[0]),
                          1);

    ACE_TString logfile(argv[1]);
    ACE_Stream<ACE_MT_SYNCH> stream;
    if (stream.push(new Logrec_Writer_Module(ACE_TEXT("Writer"))) != -1
            && stream.push(new Logrec_Separator_Module(ACE_TEXT("Separator"))) != -1
            && stream.push(new Logrec_Formatter_Module(ACE_TEXT("Formatter"))) != -1
            && stream.push(new Logrec_Reader_Module(logfile)) != -1)
        return ACE_Thread_Manager::instance()->wait() == 0 ? 0 : 1;

    return 1;
}
// vim: set et ts=4 sts=4 sw=4:
