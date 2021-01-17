#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/reboot.h>

int main()
{
    const char *user = getenv("USER");
    if (strcmp(user, "root") == 0)
    {
        sync(); // Let's commit cache to disk
        reboot(RB_AUTOBOOT);
    }
    else
    {
        printf("Root privileges required!\n");
    }
    return 0;
}
