/*
 * Prints environment list
 */
#include "tlpi_hdr.h"

extern char **environ;

int main(int argc, char *argv[] /*, char *envp[] */)
{
    char **p_env;
    for (p_env = environ; *p_env != NULL; p_env++)
    {
        puts(*p_env);
    }
    return 0;
}
