#ifndef MDS_ERROR_FUNTIONS_H
#define MDS_ERROR_FUNTIONS_H

/*
 * Prints the error on standar error, and prints the value of errno
 */
void errMsg(const char *format, ...);

#ifdef __GNUC__

    /* This macro stops 'gcc -Wall' complaining that "control reaches
       end of non-void function" if we use the following functions to
       terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/* To diagnose errors from system calls and library functions */

/*
 * Operates like errMsg but also terminate the program, and in case of
 * non-empty env variable MDS_DUMPCORE calls abort to produce a core dump
 */
void errExit(const char *format, ...) NORETURN ;

/*
 * It doesn’t flush standard output before printing the error message.
 * It terminates the process by calling _exit() instead of exit(). This causes the process to terminate without flushing stdio buffers or invoking exit handlers.
 */
void err_exit(const char *format, ...) NORETURN ;

/*
 * Mainly in programs that empley POSIX threads API
 */
void errExitEN(int errnum, const char *format, ...) NORETURN ;

/*
 * Used to diagnose general errors, including errors from library functions that don’t set errno.
 */
void fatal(const char *format, ...) NORETURN ;

/*
 * Used to dignose errors in command-line argument usage
 */
void usageErr(const char *format, ...) NORETURN ;

/*
 * Used to diagnose error in command-line argument specific to a program
 */
void cmdLineErr(const char *format, ...) NORETURN ;

#endif
