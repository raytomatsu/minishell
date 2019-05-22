#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <iostream>

class Activity
{
public:
    Activity();
    Activity(int _id, std::string eep, long long _time);

    std::string getEntryExitPeak() const;

    long long getTime() const;

    int getId() const;

private:
    int id;//run id, aka udp #
    std::string entryExitPeak;//the actual udp message
    long long time;
};

#endif // ACTIVITY_H
