#ifndef ZEITMESSUNG_H
#define ZEITMESSUNG_H

#if defined(__unix__) || defined(__APPLE)
#define _POSIX_C_SOURCE 200809L

#include <time.h>
#include <stddef.h>
#endif // __unix__

#ifdef _WIN32
#include <time.h>
#include <windows.h>
#endif // _WIN32
/**
 * @brief Data type representing a time value. The underlying data type may
 * differ on different systems.
 */
typedef long long unsigned t_timevalue;

/**
 * @brief Data structure representing an individual stopwatch. There may be
 * created several stopwatch variables, thus making it possible to have stopwatches
 * measuring different (e.g. nested) code sequences in parallel.
 * The data fields contained in this structure are not part of the user interface,
 * data items of type t_stopwatch should be accessed by functions provided by this
 * library, exclusively. 
 */
struct t_stopwatch
{
    t_timevalue  TimestampStart;
    t_timevalue  ResultingTime;
    int isRunning;
};

typedef struct t_stopwatch t_stopwatch;


t_timevalue get_posix_clock_time();
void startStopwatch(t_stopwatch* theWatch);
t_timevalue restartStopwatch(t_stopwatch* theWatch);
t_timevalue stopStopwatch(t_stopwatch* theWatch);
t_timevalue readStopwatch(t_stopwatch* theWatch);
t_timevalue evaluateStopwatch(t_stopwatch* theWatch);


#endif // ZEITMESSUNG_H
