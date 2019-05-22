#include "sense.h"

Sense::Sense()
{

}

Sense::Sense(unsigned short int hiveID, unsigned long long time){
    this->hiveID = hiveID;
    this->time = time;
    for(int i = 0; i < 10; i++){
        std::bitset<8> temp;
        bds.push_back(temp);
        for(int k = 0; k < 8; k++)
            bds.at(i)[k] = 0;
    }
}

Sense::~Sense(){}



unsigned short int Sense::getHiveID(){
    return hiveID;
}

unsigned long long Sense::getTime(){
    return time;
}



void Sense::addSensors(unsigned short int boardNum, unsigned short int sensors){
    //boards[boardNum] = std::bitset<8>(sensors);
    bds.at(boardNum) = std::bitset<8>(sensors);
}

bool Sense::getSensor(unsigned short int boardNum, unsigned short int sensorNum){
    //return boards[boardNum][sensorNum-1];
    return bds.at(boardNum)[sensorNum-1];
}

void Sense::setSensor(unsigned short int boardNum, unsigned short int sensorNum, bool value){
    //boards[boardNum][sensorNum-1] = value;
    bds.at(boardNum)[sensorNum-1] = value;
}
