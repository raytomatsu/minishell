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



class UDPMessage
{
public:
    UDPMessage();
    std::string generate(std::string hiveId, std::chrono::system_clock::time_point t, std::vector<std::vector<int>> boards);
    void generate_random(int seed);
    void read_file(std::string filename);
    void send_to_db(std::string msg, int hid, unsigned long long time);
private:
    std::string message;
    std::vector<int> lambda;
    std::vector<double> times;
    std::priority_queue<double, std::vector<double>, std::greater<double>> queue;
};

#endif // UDPMESSAGE_H
