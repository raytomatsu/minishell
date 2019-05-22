#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
    Event();
    Event(unsigned short int hiveID, unsigned long long time, std::string type);
    ~Event();

    unsigned short int getHiveID();
    unsigned long long getTime();
    std::string getType();
    std::string toString();


private:
    unsigned short int hiveID;
    unsigned long long time;
    std::string type;//"Entry", "Exit", or "Peek"

};

#endif // EVENT_H
