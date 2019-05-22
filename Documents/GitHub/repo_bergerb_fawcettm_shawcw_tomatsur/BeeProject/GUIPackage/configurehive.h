#ifndef CONFIGUREHIVE_H
#define CONFIGUREHIVE_H

#include <string>
using namespace std;

class ConfigureHive
{
public:
    ConfigureHive();
    string getSeason();
    string getWeather();
    string getLocation();

private:
    string season;
    string weather;
    string location;

};

#endif // CONFIGUREHIVE_H
