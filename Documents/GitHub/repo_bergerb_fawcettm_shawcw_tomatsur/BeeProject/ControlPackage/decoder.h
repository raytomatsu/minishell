#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>

#include "sense.h"
#include "event.h"
#include "activitycontainer.h"
#include "activity.h"
#include "controller.h"

class Decoder
{
public:
    Decoder();
    Decoder(std::string filename);
    ~Decoder();

    std::vector<int> decode(int hiveID, std::string season, int temperature);
    std::string getFilename();

private:
    std::string filename;

};

#endif // DECODER_H
