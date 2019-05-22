#include "event.h"

/**
 * Event is an object that contains the info about the DECODED udp message. it has been translated into entries, exits and peaks at this p
 * point.
 */


Event::Event()
{

}

Event::Event(unsigned short int hiveID, unsigned long long time, std::string type){
    this->hiveID = hiveID;
    this->time = time;
    this->type = type;
}

Event::~Event(){}


unsigned short int Event::getHiveID(){
    return hiveID;
}

unsigned long long Event::getTime(){
    return time;
}

std::string Event::getType(){
    return type;
}


std::string Event::toString(){
    std::string t = std::to_string(time);
    return t + " " + type;
}
