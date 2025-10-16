#include "Zeitmessung.h"
#include <time.h>

t_timevalue  get_clock_time ()
{
#if defined(__unix__) || defined(__APPLE)

    struct timespec ts;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
    {
        return (t_timevalue) ((t_timevalue)ts.tv_sec * 1000000000ULL + ts.tv_nsec );
    }
    else
    {
        return 0;
    }
#endif // __unix__
#ifdef _WIN32
    LARGE_INTEGER TickFrequecny;
    LARGE_INTEGER TimerValue;
    QueryPerformanceCounter(&TimerValue);
    QueryPerformanceFrequency(&TickFrequecny);
    t_timevalue result=TimerValue.QuadPart*1000000000ULL/TickFrequecny.QuadPart;
    return result;
#endif // _WIN32
}

/**
 @brief This function starts the stopwatch handed over via the parameter. Time measurement 
starts always at zero. 
@parameter theWatch specifies that watch to be started, as the user might want to handle several different stopwtches within the program.
 */
void startStopwatch(t_stopwatch* theWatch)
{
    theWatch->TimestampStart=get_clock_time();
    theWatch->ResultingTime=0;
    theWatch->isRunning=1;
}

/**
 @brief This function restarts the stopwatch handed over via the parameter without resetting the measurement to zero and must only be caled for running or stopped stopwatches.  
@parameter theWatch specifies that watch to be restarted, as the user might want to handle several different stopwtches within the program.
 @return The functon returns the current value of the measured time.
 */
t_timevalue restartStopwatch(t_stopwatch* theWatch)
{
    t_timevalue newstart=get_clock_time();
    if (theWatch->isRunning)
    {
        theWatch->ResultingTime+=newstart-theWatch->TimestampStart;
    }
    theWatch->TimestampStart=newstart;
    return theWatch->ResultingTime;
}

/**
 @brief This function stops the stopwatch handed over via the parameter. 
@parameter theWatch specifies that watch to be stopped. This functions should only be called for running stopwatches. Otherwise, the behaviour ist undefined.
 @return The functon returns the value of the measured time.
 */
t_timevalue stopStopwatch(t_stopwatch* theWatch)
{
    theWatch->ResultingTime += get_clock_time()-theWatch->TimestampStart;
    theWatch->isRunning=0;
    return theWatch->ResultingTime;
}

/**
 @brief This function reads out the stopwatch handed over via the parameter. 
@parameter theWatch specifies which watch to be evaluated. This functions can be called for running stopwatches and stopped stopwatches. Running it repeatedly on a stopwatch is allowd and will not influence the state of the stopwatch.
 @return The functon returns the value of the measured time.
 */
t_timevalue evaluateStopwatch(t_stopwatch* theWatch)
{
    return theWatch->ResultingTime + get_clock_time()-theWatch->TimestampStart;
}

/**
 @brief This function reads out the stopwatch handed over via the parameter. 
@parameter theWatch specifies which watch to be read out. This function must be called for stopped stopwatches exclusively, for running or not yet started stopwatches the result will be undefined. Running it repeatedly on a stopwatch is allowd and will not influence the state of the stopwatch.
 @return The functon returns the value of the measured time.
 */
t_timevalue readStopwatch(t_stopwatch* theWatch)
{
    return theWatch->ResultingTime;
}
