#include "param.h"
// Retorna o tempo atual 
struct tm *timeGetTime(){
    time_t raw_time;
    struct tm *actual_time;
    time(&raw_time);
    actual_time = localtime(&raw_time);
    return actual_time;
}
