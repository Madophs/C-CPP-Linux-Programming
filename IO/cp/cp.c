#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 512
#endif

int main(int argc, char *argv[])
{
    if (argc != 3 || (argc > 1 && strcmp(argv[1], "--help") == 0))
    {
        usageErr("%s\n", "./cp SOURCE DEST");
    }

    int sourceFd, destFd, openFlags;
    mode_t filePerms;
    ssize_t numBytesRead;

    const char *sourceFile = argv[1];

    sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1)
        errExit("opening file %s.", sourceFile);

    openFlags = O_CREAT | O_TRUNC | O_RDWR;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw

    const char *destFile = argv[2];

    destFd = open(destFile, openFlags, filePerms);

    if (destFd == -1)
        errExit("opening dest file");

    /* Time to transfer the contents */

    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);

    while ((numBytesRead = read(sourceFd, buf, BUF_SIZE)) > 0)
    {
        if (write(destFd, buf, (ssize_t)numBytesRead) != numBytesRead)
            fatal("Couldn't write the whole buffer");
    }

    if (numBytesRead == -1)
        errExit("read");

    if (close(sourceFd) == -1)
        errExit("close source");
    if (close(destFd) == -1)
        errExit("close dest");

    return EXIT_SUCCESS;
}
