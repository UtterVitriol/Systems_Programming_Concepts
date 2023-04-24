#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>

typedef void (*f_exploit_t)(void);

static void
launch_exploit(char *libpath)
{
    void *h_submission = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);
    if (NULL == h_submission)
    {
        fprintf(stderr, "error: could not open library: %s\n", dlerror());
        exit(-1);
    }

    f_exploit_t exploit = dlsym(h_submission, "exploit");
    if (NULL == exploit)
    {
        fprintf(stderr, "error: could find exploit symbol: %s\n", dlerror());
        exit(-2);
    }

    puts("Calling exploit...");
    exploit();
}

int
main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s lib\n", argv[0]);
        return -1;
    }

    pid_t child = fork();

    if (child < 0)
    {
        perror("fork failed");
        return -2;
    }
    else if (!child)
    {
        launch_exploit(argv[1]);
        fputs("Returned from exploit\n", stderr);
        return 0;
    }

    int   status     = 0;
    pid_t waited_pid = wait(&status);

    if (waited_pid < 0)
    {
        perror("wait failed");
        return -3;
    }
    else if (waited_pid != child)
    {
        fprintf(stderr,
                "unknown child detected: %d (exited with %d)\n",
                waited_pid,
                status);
        return -4;
    }

    if (status)
    {
        fprintf(stderr, "child exited with status of %d\n", status);
    }
    else
    {
        fputs("child exited cleanly\n", stderr);
    }

    return status;
}