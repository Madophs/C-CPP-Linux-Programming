#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

/**
 * ./seek_io ./temp.txt whello s100 wcommon s0 r1000
 */

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
    }
    char *filename = argv[1];
    int fd = open(filename,
            O_CREAT | O_RDWR,
            S_IRUSR, S_IWUSR, S_IRGRP, S_IWGRP, S_IROTH, S_IWOTH);
    if (fd == -1)
        errExit("opening file %s", filename);

    char *buf;
    ssize_t len, nbytes;
    off_t offset;
    char *str;
    for (int i = 2; i < argc; ++i)
    {
        char option = argv[i][0];
        switch (option)
        {
            case 'r':
            case 'R':
                len = getLong(&argv[i][1], GN_ANY_BASE, "len");
                buf = malloc(len);
                nbytes = read(fd, buf, len);
                if (nbytes == -1)
                    errExit("read");

                if (nbytes == 0)
                {
                    printf("%s: end of file\n", argv[i]);
                }
                else
                {
                    printf("%s: ", argv[i]);
                    for (int j = 0; j < nbytes; ++j)
                    {
                        if (argv[i][0] == 'r')
                        {
                            printf("%c", (isprint((unsigned char)buf[j]) ? buf[j] : '?'));
                        }
                        else
                        {
                            printf("%02x", ((unsigned char)buf[j]));
                        }
                    }
                    printf("\n");
                }
                free(buf);
                break;
            case 'w':
                buf = &argv[i][1];
                len = strlen(buf);
                nbytes = write(fd, buf, len);
                if (nbytes == -1)
                    errExit("write on %s", argv[i]);
                printf("%s wrote %ld bytes\n", argv[i], nbytes);
                break;
            case 's':
                offset = getLong(&argv[i][1], GN_ANY_BASE, "len");
                if (lseek(fd, offset, SEEK_SET) == -1)
                    errExit("lseek");
                printf("%s seek succeeded\n", argv[i]);
                break;
        }
    }
    return EXIT_SUCCESS;
}
