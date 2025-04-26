#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

struct Timer
{
        double unixStart;
        double elapsed;

        Timer()
        {
                elapsed = 0;
                start();
        }

        inline void start()
        {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                unixStart = tv.tv_sec + tv.tv_usec / 1000000.0;
        }

        inline void update()
        {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                double unixNow = tv.tv_sec + tv.tv_usec / 1000000.0;
                elapsed = unixNow - unixStart;
        }
};

#endif
