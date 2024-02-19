/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-07     Meco Man     combine gcc armcc iccarm
 * 2021-02-12     Meco Man     move all definitions located in <clock_time.h> to this file
 */

#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

#include <rtconfig.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#ifdef _WIN32
typedef __time64_t time_t;
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#undef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC RT_TICK_PER_SECOND

/* timezone */
#define DST_NONE    0   /* not on dst */
#define DST_USA     1   /* USA style dst */
#define DST_AUST    2   /* Australian style dst */
#define DST_WET     3   /* Western European dst */
#define DST_MET     4   /* Middle European dst */
#define DST_EET     5   /* Eastern European dst */
#define DST_CAN     6   /* Canada */
#define DST_GB      7   /* Great Britain and Eire */
#define DST_RUM     8   /* Rumania */
#define DST_TUR     9   /* Turkey */
#define DST_AUSTALT 10  /* Australian style with shift in 1986 */

struct itimerspec;

struct timezone
{
    int tz_minuteswest;   /* minutes west of Greenwich */
    int tz_dsttime;       /* type of dst correction */
};

#if defined(_GNU_SOURCE) && (defined(__x86_64__) || defined(__i386__))
/* linux x86 platform gcc use! */
#define _TIMEVAL_DEFINED
/* Values for the first argument to `getitimer' and `setitimer'.  */
enum __itimer_which
{
    /* Timers run in real time.  */
    ITIMER_REAL = 0,
#define ITIMER_REAL ITIMER_REAL
    /* Timers run only when the process is executing.  */
    ITIMER_VIRTUAL = 1,
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
    /* Timers run when the process is executing and when
       the system is executing on behalf of the process.  */
    ITIMER_PROF = 2
#define ITIMER_PROF ITIMER_PROF
};

struct itimerval
{
    /* Value to put into `it_value' when the timer expires.  */
    struct timeval it_interval;
    /* Time to the next timer expiration.  */
    struct timeval it_value;
};
#endif /* defined(_GNU_SOURCE) && (defined(__x86_64__) || defined(__i386__)) */

#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED
struct timeval
{
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* and microseconds */
};
#endif /* _TIMEVAL_DEFINED */

#if defined(__ARMCC_VERSION) || defined(_WIN32) || (defined(__ICCARM__) && (__VER__ < 8010001))
struct timespec
{
    time_t  tv_sec;     /* seconds */
    long    tv_nsec;    /* and nanoseconds */
};
#endif /* defined(__ARMCC_VERSION) || defined(_WIN32) || (defined(__ICCARM__) && (__VER__ < 8010001)) */

#if !(defined(__GNUC__) && !defined(__ARMCC_VERSION)/*GCC*/)
/*
 * Structure defined by POSIX.1b to be like a itimerval, but with
 * timespecs. Used in the timer_*() system calls.
 */
struct itimerspec
{
    struct timespec  it_interval;
    struct timespec  it_value;
};
#endif /* !(defined(__GNUC__) && !defined(__ARMCC_VERSION)) */

int stime(const time_t *t);
time_t timegm(struct tm * const t);
int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

#if defined(__ARMCC_VERSION) || defined (__ICCARM__) || defined(_WIN32)
struct tm *gmtime_r(const time_t *timep, struct tm *r);
char* asctime_r(const struct tm *t, char *buf);
char *ctime_r(const time_t * tim_p, char * result);
struct tm* localtime_r(const time_t* t, struct tm* r);
#endif /* defined(__ARMCC_VERSION) || defined (__ICCARM__) || defined(_WIN32) */

#ifdef _WIN32
struct tm* gmtime(const time_t* t);
struct tm* localtime(const time_t* t);
time_t mktime(struct tm* const t);
char* ctime(const time_t* tim_p);
time_t time(time_t* t);
#endif /* _WIN32 */

#ifdef RT_USING_POSIX_DELAY
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
#endif /* RT_USING_POSIX_DELAY */

#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

#if defined(RT_USING_POSIX_CLOCK) || defined (RT_USING_POSIX_TIMER)
/* POSIX clock and timer */

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME      1
#endif /* CLOCK_REALTIME */

#define CLOCK_CPUTIME_ID    2

#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID CLOCK_CPUTIME_ID
#endif /* CLOCK_PROCESS_CPUTIME_ID */

#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID  CLOCK_CPUTIME_ID
#endif /* CLOCK_THREAD_CPUTIME_ID */

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC     4
#endif /* CLOCK_MONOTONIC */

#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME       4
#endif /* TIMER_ABSTIME */

#ifdef CLOCK_TAI
#define CLOCK_ID_MAX CLOCK_TAI
#else
#define CLOCK_ID_MAX CLOCK_MONOTONIC
#endif
#endif /* defined(RT_USING_POSIX_CLOCK) || defined (RT_USING_POSIX_TIMER) */

#ifdef RT_USING_POSIX_CLOCK
int clock_getres  (clockid_t clockid, struct timespec *res);
int clock_gettime (clockid_t clockid, struct timespec *tp);
int clock_settime (clockid_t clockid, const struct timespec *tp);
int clock_nanosleep(clockid_t clockid, int flags, const struct timespec *rqtp, struct timespec *rmtp);
int rt_timespec_to_tick(const struct timespec *time);
#endif /* RT_USING_POSIX_CLOCK */

#ifdef RT_USING_POSIX_TIMER
#include <sys/signal.h>
int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid);
int timer_delete(timer_t timerid);
int timer_getoverrun(timer_t timerid);
int timer_gettime(timer_t timerid, struct itimerspec *its);
int timer_settime(timer_t timerid, int flags, const struct itimerspec *value, struct itimerspec *ovalue);
#endif /* RT_USING_POSIX_TIMER */

/* timezone */
void tz_set(int8_t tz);
int8_t tz_get(void);
int8_t tz_is_dst(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SYS_TIME_H_ */
