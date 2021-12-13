#include "param.h"
// Returns the actual time 
struct tm *timeGetTime(){
    time_t raw_time;
    struct tm *actual_time;
    time(&raw_time);
    actual_time = localtime(&raw_time);
    return actual_time;
}
