#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

#ifdef __GNUC__
// Informs the compiler that the function does not return. The compiler can then perform optimizations by removing code that is never reached.
__attribute__((__noreturn__))
#endif

static void terminateProcess(Boolean useExit3)
{
    char *s;

    s = getenv("MDS_DUMPCORE");

    if (s != NULL && *s != '\n')
        abort(); // Abort and create a coredump
    else if (useExit3)
        exit(EXIT_FAILURE); // For main processes
    else
        _exit(EXIT_FAILURE); // For calling processes (child process)
}

static void outputError(Boolean useErr, int err, Boolean flushStdout,
        const char *format, va_list ap)
{
    #define BUF_SIZE 1024
    #define MSG_SIZE 500
    char buf[BUF_SIZE], errMsg[MSG_SIZE], userMsg[MSG_SIZE];

    vsnprintf(userMsg, MSG_SIZE, format, ap);

    if (useErr)
    {
        snprintf(errMsg, MSG_SIZE, "[%s %s]",
            (err > 0 && err < MAX_ENAME) ? ename[err] : "Unknown", strerror(err));
    }
    else
    {
		snprintf(errMsg, MSG_SIZE, ":");
    }

	snprintf(buf, BUF_SIZE, "ERROR: %s %s\n", errMsg, userMsg);

	if (flushStdout)
		fflush(stdout); // Any pending stdout

	fputs(buf, stdout);
	fflush(stdout); // Just in case
}

void errMsg(const char *format, ...)
{
    va_list argList;

    int32_t savedErrno = errno;

    va_start(argList, format);
    outputError(TRUE, savedErrno, TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char *format, ...)
{
    va_list argList;

    int32_t savedErrno = errno;

    va_start(argList, format);
    outputError(TRUE, savedErrno, TRUE, format, argList);
    va_end(argList);

    terminateProcess(TRUE);
}

/*
 * Terminate child process
 */
void err_exit(const char *format, ...)
{
    va_list argList;

    int32_t savedErrno = errno;

    va_start(argList, format);
    outputError(TRUE, savedErrno, FALSE, format, argList);
    va_end(argList);

    terminateProcess(FALSE);
}


void errExitEN(int errNum, const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errNum, TRUE, format, argList);
    va_end(argList);

    terminateProcess(TRUE);
}

void fatal(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);

    terminateProcess(TRUE);
}

void usageErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}
