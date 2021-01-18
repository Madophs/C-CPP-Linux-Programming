#include <tlpi_hdr.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

int main(int argc, char *argv[])
{
    if (argc < 2)
        usageErr("./tee -a(append optional) file.\n");

    int opt;
    int append = 0;
    char *filename;
    while ((opt = getopt(argc, argv, "a::f:")) != -1)
    {
        switch (opt)
        {
            case 'a':
                append = 1;
                break;
            case 'f':
                filename = optarg;
                break;
            default:
                errExit("Invalid argument");
        }
    }

    mode_t filePerms;
    int outputFd, openFlags;

    openFlags = O_RDWR | O_CREAT | (append ? O_APPEND : O_TRUNC);
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw

    outputFd = open(filename, openFlags, filePerms);

    if (outputFd == -1)
        errExit("open");

    /* Keep reading from stdin */

    char *input = NULL;
    size_t lineLength = BUFFER_SIZE;
    ssize_t bytesRead;
    while ((bytesRead = getline(&input, &lineLength, stdin)) != -1)
    {
        printf("%s", input);
        write(outputFd, input, bytesRead);
        memset(input, 0, lineLength);
    }

    if (bytesRead == -1 && errno != 0)
        errExit("getline");

    close(outputFd);
    return 0;
}
