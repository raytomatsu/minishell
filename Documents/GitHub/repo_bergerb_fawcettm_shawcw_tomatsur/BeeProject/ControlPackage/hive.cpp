#include "hive.h"

/**
 * Hive -- object created by input in the GUI containing the variables that configure a
 * specific hive.
 **/

Hive::Hive(){

}
Hive::Hive(int hiveID, std::string season, int temp, std::string location)
{
    this->id = hiveID;
    this->season = season;
    this->temperature = temp;
    this->location = location;
}

int Hive::getTemperature() const
{
    return temperature;
}

std::string Hive::getSeason() const
{
    return season;
}

std::string Hive::getLocation() const
{
    return location;
}

int Hive::getId() const
{
    return id;
}

