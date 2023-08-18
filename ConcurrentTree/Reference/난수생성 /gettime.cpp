#include <time.h>
// https : // ryanclaire.blogspot.com/2021/02/create-gettickcount-using-clockgettime.html

unsigned long GetTickCount()
{
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (unsigned long)(tp.tv_sec * 1000 + tp.tv_nsec / 1000000);
}
