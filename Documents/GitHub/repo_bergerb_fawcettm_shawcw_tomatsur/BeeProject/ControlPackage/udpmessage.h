#ifndef UDPMESSAGE_H
#define UDPMESSAGE_H

#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <queue>
#include <thread>
#include "../DBPackage/dbhive.h"
#include "../DBPackage/dbtool.h"
#include "../DBPackage/dbtable.h"
#include "decoder.h"

#include "controller.h"


class UDPMessage
{
public:
    UDPMessage();
    std::string generate(std::string hiveId, std::chrono::system_clock::time_point t, std::vector<std::vector<int>> boards);
    void generate_random(int seed, std::string hiveID, std::chrono::system_clock::time_point start, std::string season, int temperature, std::string special, int numChunks);
private:
    std::string message;
    std::vector<double> times;
    std::priority_queue<double, std::vector<double>, std::greater<double>> queue;
    Controller c;
};

#endif // UDPMESSAGE_H
