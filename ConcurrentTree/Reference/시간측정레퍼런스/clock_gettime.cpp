/* 참고 블로그
https://mkblog.co.kr/c-measure-time-clock-gettime-function/
*/
// 멀티스레드를 사용하는 경우 clock() 함수는 잘못된 결과가 출력되는 경우가 발생한다고 하여,
// 블로그에서는 clock_gettime() 함수 사용
#include <stdio.h>
#include <time.h>

#define MAX 1000000

//
int main()
{

    // MK: 시작/끝 시간을 측정하기 위해서 추가함 (time.h 필요)
    struct timespec begin, end;
    double tmpValue = 0.0;

    // MK: 연산 시작과 함께 시간을 측정함
    clock_gettime(CLOCK_MONOTONIC, &begin);
    for (int i = 0; i < MAX; i++)
    {
        tmpValue += i;
    }

    // MK: 연산이 끝나면 시간을 측정함
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Value: %lf\n", tmpValue);

    // MK: 측정한 시간을 Nano, Micro, Milli, Second 단위로 출력함
    long time = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
    printf("Time (Nano): %ld\n", time);
    printf("Time (Micro): %lf\n", (double)time / 1000);
    printf("Time (Milli): %lf\n", (double)time / 1000000);
    printf("Time (Second): %lf\n", (double)time / 1000000000);

    return 0;
}

/* 멤버 변수
struct timespec {
    time_t   tv_sec;       // seconds
    long tv_nsec; // nanoseconds
};
*/