#include <ace/OS.h>
#include <ace/ACE.h>
#include <ace/Process.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    ACE_Process_Options options;
    FILE *fp = 0;
    char *n_env = 0;
    int n;

    if (argc == 1) {
        n_env = ACE_OS::getenv("FACTORIAL");
        n = n_env == 0 ? 10 : atoi(n_env);
        options.command_line("%s %d", argv[0], n - 1);
        const char *working_dir = ACE_OS::getenv("WORKING_DIR");
        if (working_dir) options.working_directory(working_dir);
        fp = fopen("factorial.log", "a");
        cout << "before setenv" << endl;
        options.setenv("PROGRAM=%s", ACE::basename(argv[0]));
        cout << "after setenv" << endl;
    } else {
        fp = fopen("factorial.log", "a");
        if (atoi(argv[1]) == 1) {
            fprintf(fp, "[%s|%d]: base case\n",
                    ACE_OS::getenv("PROGRAM"), ACE_OS::getpid());
            fclose(fp);
            return 1;
        } else {
            n = atoi(argv[1]);
            options.command_line("%s %d", argv[0], n - 1);
        }
    }

    ACE_Process child;
    child.spawn(options);
    child.wait();
    int factorial = n * child.return_value();
    fprintf(fp, "[%s|%d]: %d! == %d\n",
            ACE_OS::getenv("PROGRAM"), ACE_OS::getpid(),
            n, factorial);
    fclose(fp);
    return factorial;
}
// vim: set et ts=4 sts=4 sw=4:
