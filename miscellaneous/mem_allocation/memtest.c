#include "tlpi_hdr.h"

int main()
{
    const int size = 100000;
    long long *ptrArr[size];

    ptrArr[0] = sbrk(0);
    printf("Heap break at %p\n", sbrk(0));
    for (unsigned int i = 0; i < size; i++)
    {
        break;
        ptrArr[i] = malloc(sizeof(long long));
        if (i % 1000 == 0)
            printf("Heap break at %p\n", sbrk(0));
    }

    ptrArr[0] = malloc(128);
    ptrArr[1] = malloc(sizeof(long long));
    ptrArr[2] = malloc(sizeof(long long));
    *ptrArr[0] = 10ll;

    for (int i = 0; i < 3; i++) {
        printf("Pointer is at %p\n", ptrArr[i]);
        printf("Pointer is at %p\n", ptrArr[i]+1);
        printf("Pointer is at %p\n", ptrArr[i]+2);
        printf("Value is %lld\n", *ptrArr[i]);
    }
    printf("Heap break at %p\n", sbrk(0));
    return 0;
}
