#include "activity.h"


/**
 * Activity is an object that holds the information about a UDP message.
 */


Activity::Activity()
{

}

Activity::Activity(int _id, std::string udp, long long _time){
    id = _id;
    entryExitPeak = udp;
    time = _time;
}

std::string Activity::getEntryExitPeak() const
{
    return entryExitPeak;
}

long long Activity::getTime() const
{
    return time;
}

int Activity::getId() const
{
    return id;
}
