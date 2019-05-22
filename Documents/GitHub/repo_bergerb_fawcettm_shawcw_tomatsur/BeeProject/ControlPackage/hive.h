#ifndef HIVE_H
#define HIVE_H
#include <iostream>

class Hive
{
public:
    Hive();
    Hive(int, std::string, int, std::string);

    int getTemperature() const;

    std::string getSeason() const;

    std::string getLocation() const;

    int getId() const;

private:
    int id;
    std::string season;
    int temperature;
    std::string location;
};

#endif // HIVE_H
