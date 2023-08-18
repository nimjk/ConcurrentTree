#ifndef _TICK_TIME_
#define _TICK_TIME_

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#else
#include <time.h>
#endif

typedef unsigned long long int tick64_t;
typedef unsigned long int tick32_t;

tick32_t get_tick_count()
{
    tick32_t tick = 0ul;

#if defined(WIN32) || defined(WIN64)
    tick = GetTickCount();
#else
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);

    tick = (tp.tv_sec * 1000ul) + (tp.tv_nsec / 1000ul / 1000ul);
#endif

    return tick;
}

tick64_t get_tick_count64()
{
    tick64_t tick = 0ull;

#if defined(WIN32) || defined(WIN64)
    tick = GetTickCount64();
#else
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);

    tick = (tp.tv_sec * 1000ull) + (tp.tv_nsec / 1000ull / 1000ull);
#endif

    return tick;
}

#endif // _TICK_TIME_