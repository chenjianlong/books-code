#include <ace/OS.h>
#include <ace/Process.h>

int main(int argc, char *argv[])
{
    ACE_Process_Options options;
    char *n_env = 0;
    int n;

    if (argc == 1) {
        n_env = ACE_OS::getenv("FACTORIAL");
        n = n_env == 0 ? 10 : atoi(n_env);
        options.command_line("%s %d", argv[0], n - 1);
    } else if (atoi(argv[1]) == 1) {
        return 1;
    } else {
        n = atoi(argv[1]);
        options.command_line("%s %d", argv[0], n - 1);
    }

    ACE_Process child;
    child.spawn(options);
    child.wait();
    return n * child.return_value();
}
// vim: set et ts=4 sts=4 sw=4:
