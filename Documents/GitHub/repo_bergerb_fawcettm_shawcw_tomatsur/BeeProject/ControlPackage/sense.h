#ifndef SENSE_H
#define SENSE_H

#include <bitset>
#include <vector>

class Sense
{
public:
    Sense();
    Sense(unsigned short int hiveID, unsigned long long time);
    ~Sense();

    unsigned short int getHiveID();
    unsigned long long getTime();

    void addSensors(unsigned short int boardNum, unsigned short int sensors);
    bool getSensor(unsigned short int boardNum, unsigned short int sensorNum);
    void setSensor(unsigned short int boardNum, unsigned short int sensorNum, bool value);



private:
    unsigned short int hiveID;
    unsigned long long time;
    std::bitset<8> boards [10];
    std::vector<std::bitset<8>> bds;

};

#endif // SENSE_H
