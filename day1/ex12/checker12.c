#include <dlfcn.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t (*f_fib_t)(uint64_t);
typedef void (*f_trace_t)(void);

static bool test_fibonacci(f_fib_t func);
static bool test_get_rip(f_trace_t func);
static bool test_dump_regs(f_trace_t func);
static bool test_trace(f_trace_t func);


int
main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s lib\n", argv[0]);
        return -1;
    }

    void *h_submission = dlopen(argv[1], RTLD_NOW | RTLD_LOCAL);
    if (NULL == h_submission)
    {
        fprintf(stderr, "error: could not open library: %s\n", dlerror());
        return -2;
    }

    bool is_passing = true;

    f_fib_t pf_fib = dlsym(h_submission, "fibonacci");
    if (pf_fib)
    {
        is_passing &= test_fibonacci(pf_fib);
    }
    else
    {
        fputs("warning: 'fibonacci' not found\n", stderr);
    }

    f_trace_t pf_rip = (f_trace_t)dlsym(h_submission, "get_rip");
    if (pf_rip)
    {
        is_passing &= test_get_rip(pf_rip);
    }
    else
    {
        fputs("warning: 'get_rip' not found\n", stderr);
    }

    f_trace_t pf_dump_regs = dlsym(h_submission, "dump_regs");
    if (pf_dump_regs)
    {
        is_passing &= test_dump_regs(pf_dump_regs);
    }
    else
    {
        fputs("warning: 'dump_regs' not found\n", stderr);
    }

    f_trace_t pf_trace = dlsym(h_submission, "trace");
    if (pf_trace)
    {
        is_passing &= test_trace(pf_trace);
    }
    else
    {
        fputs("warning: 'trace' not found\n", stderr);
    }

    dlclose(h_submission);
    if (!is_passing)
    {
        fputs("error: failed one or more tests\n", stderr);
    }
    return is_passing ? 0 : -3;
}

static uint64_t
fibonacci_(uint64_t n)
{
    uint64_t prev = 1;
    uint64_t curr = 1;
    for (uint64_t i = 1; i < n; i++)
    {
        curr += prev;
        prev = curr - prev;
    }
    return curr;
}

static bool
test_fibonacci(f_fib_t func)
{
    for (uint64_t n = 0; n < 15; n++)
    {
        if (fibonacci_(n) != func(n))
        {
            fprintf(stderr,
                    "error: f(%lu): received %lu, expected %lu\n",
                    n,
                    func(n),
                    fibonacci_(n));
            return false;
        }
    }
    return true;
}

static bool
test_get_rip(f_trace_t func)
{
    func();
    return true;
}

static bool
test_dump_regs(f_trace_t func)
{
    func();
    return true;
}

static bool
test_trace(f_trace_t func)
{
    func();
    return true;
}