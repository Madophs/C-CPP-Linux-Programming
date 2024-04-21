#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "get_num.h"

static void gnFail(const char *fname, const char *errMsg, const char *arg, const char *name)
{
    fprintf(stderr, "%s error", fname);

    if (name != NULL)
        fprintf(stderr, " (in %s)", name);
    fprintf(stderr, ": %s\n", errMsg);

    if (arg != NULL && *arg != '\0')
        fprintf(stderr, "        funny text: %s\n", arg);

    exit(EXIT_FAILURE);
}

static long getNum(const char *fname, const char *arg, int flags, const char *name)
{
    long res;
    char *endptr;
    int base;

    if (arg == NULL || *arg == '\n')
        gnFail(fname, "null or empty string", arg, name);

    base = (flags & GN_ANY_BASE) ? 0 :
        (flags & GN_BASE_8) ? 8 :
        (flags & GN_BASE_16) ? 16 : 10;

    errno = 0; // reset errno to check for errors

    res = strtol(arg, &endptr, base);

    if (errno != 0)
        gnFail(fname, "strtol function failed", arg, name);
    if (*endptr != '\0')
        gnFail(fname, "non numeric characters", arg, name);

    if ((flags & GN_NONNEG) && res < 0)
        gnFail(fname, "must be non-negative value", arg, name);
    if ((flags & GN_GT_0) && res <= 0)
        gnFail(fname, "value most be greater than zero", arg, name);
    return res;
}

long getLong(const char *arg, int flags, const char *name)
{
    return getNum("getLong", arg, flags, name);
}

int getInt(const char *arg, int flags, const char *name)
{
    long res = getNum("getInt", arg, flags, name);

    if (res < INT_MIN || res > INT_MAX)
        gnFail("getInt", "value out of range", arg, name);

    return (int)res;
}
