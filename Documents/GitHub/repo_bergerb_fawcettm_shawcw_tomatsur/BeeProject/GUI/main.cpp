#include <iostream>

#include <string>
#include <bitset>
#include <vector>
#include <fstream>

#include "sense.h"
#include "event.h"

int main()
{
    //Boiled down important info:

    //main.cpp file in some folder or other that can be run to read in a
    //text file of UDP messages and convert them into a vector of
    //structs containing entry/exit information and datetimes.

    //Typical hive has 10 boards (40 gates), each like:
    //GATE       |  A  |  B  |  C  |  D  |
    //INNER      |  1  |  2  |  3  |  4  |
    //OUTER      |  8  |  7  |  6  |  5  |

    //Example input:
    //HC0002-D18.12.19T13.43.16000-B0B1B16B0B0B0B0B0B0B0
    //Hive # - Day.Month.YearTHour.Minute.SecondMilliseconds-B...
    //The number of characters leading up to the first "B" may change, so search for first "B"

    //HC0002: device ID for the hive from which the UDP originates
    //D18.12.19T13.43.16000: date and time
    //B0B1B16B0B0B0B0B0B0B0: status of boards. The B chars are dividers between boards.
        //The example message indicates that boards 2 and and 3 show activity on sensors 1 and 5 respectively.

    //The numbers are 8-bit-long binary numbers, one bit for each sensor, converted to decimal

    //Read in decimal in string


//    std::cout << "Hello World!" << std::endl;
//    std::string s = std::bitset<8>(5).to_string();//.toString()
//    std::cout << s << std::endl;

//    std::bitset<8> t(std::string("10100000"));
//    std::cout << t.to_ulong() << std::endl;




    std::string filename = "../output.txt";
    //File full of UDPs to decode

    int threshold = 1000;
    //Number of milliseconds between an outer and inner sense,
    //or inner and outer to deems it an entry or exit
    //ie. if an inner is activated, but a long time passes before
    //another sense, then it was probably a peek not a pass-through
    //ASSUMPTION: if it takes longer than threshold, it was a PEEK - NOT an Entry/Exit


    //Struct holders:
    int guessNumUDPs = 1000000;//used for initial vector sizes:
    int guessNumEvents = 10000;
    std::vector<Sense> senses;
    senses.reserve(guessNumUDPs);
    std::vector<Event> events;
    events.reserve(guessNumUDPs);


    //File Reading:

    std::string current;
    std::ifstream file;
    file.open(filename);

    if(!file){//Checks for if the file is not found/not openable
        std::cout << "File not found/not openable." <<std::endl;
        exit(1);//Exits program
    }

    //Gathering Data from UDPs:

    while(!file.eof()){//while not at the end of the file
        file >> current;//read in the current UDP
        if(current.size()<10) break; //if end of file extra space or enter instead of just final UDP
        //std::cout << current <<std::endl;


        //HC0002-D18.12.19T13.43.16000-B0B1B16B0B0B0B0B0B0B0
        //Hive # - Day.Month.YearTHour.Minute.SecondMilliseconds-B...

        unsigned int pieces[17];
        current = current.substr(2);
        int index = current.find("-");
        pieces[0] = std::stoi(current.substr(0, index));//Hive number
        current = current.substr(index+2);

        index = current.find(".");
        pieces[1] = std::stoi(current.substr(0, index));//Day
        current = current.substr(index+1);

        index = current.find(".");
        pieces[2] = std::stoi(current.substr(0,index));//Month
        current = current.substr(index+1);

        index = current.find("T");
        pieces[3] = std::stoi(current.substr(0,index));//Year
        current = current.substr(index+1);

        index = current.find(".");
        pieces[4] = std::stoi(current.substr(0,index));//Hour
        current = current.substr(index+1);

        index = current.find(".");
        pieces[5] = std::stoi(current.substr(0,index));//Minute
        current = current.substr(index+1);

        index = current.find("-");
        pieces[6] = std::stoi(current.substr(0,index));//Milliseconds
        current = current.substr(index+2);

        //B's
        index = current.find("B");
        pieces[7] = std::stoi(current.substr(0,index));//Board 1
        current = current.substr(index+1);
        index = current.find("B");
        pieces[8] = std::stoi(current.substr(0,index));//Board 2
        current = current.substr(index+1);
        index = current.find("B");
        pieces[9] = std::stoi(current.substr(0,index));//Board 3
        current = current.substr(index+1);
        index = current.find("B");
        pieces[10] = std::stoi(current.substr(0,index));//Board 4
        current = current.substr(index+1);
        index = current.find("B");
        pieces[11] = std::stoi(current.substr(0,index));//Board 5
        current = current.substr(index+1);
        index = current.find("B");
        pieces[12] = std::stoi(current.substr(0,index));//Board 6
        current = current.substr(index+1);
        index = current.find("B");
        pieces[13] = std::stoi(current.substr(0,index));//Board 7
        current = current.substr(index+1);
        index = current.find("B");
        pieces[14] = std::stoi(current.substr(0,index));//Board 8
        current = current.substr(index+1);
        index = current.find("B");
        pieces[15] = std::stoi(current.substr(0,index));//Board 9
        current = current.substr(index+1);
        pieces[16] = std::stoi(current);//Board 10

        int days = 0;
        if(pieces[2]==1) days = pieces[1];
        else if(pieces[2]==2) days += 31 + pieces[1];//31;
        else if(pieces[2]==3) days += 59 + pieces[1];//31+28;
        else if(pieces[2]==4) days += 90 + pieces[1];//31+28+31;
        else if(pieces[2]==5) days += 120 + pieces[1];//31+28+31+30;
        else if(pieces[2]==6) days += 151 + pieces[1];//31+28+31+30+31;
        else if(pieces[2]==7) days += 181 + pieces[1];//31+28+31+30+31+30;
        else if(pieces[2]==8) days += 212 + pieces[1];//31+28+31+30+31+30+31;
        else if(pieces[2]==9) days += 243 + pieces[1];//31+28+31+30+31+30+31+31;
        else if(pieces[2]==10) days += 273 + pieces[1];//31+28+31+30+31+30+31+31+30;
        else if(pieces[2]==11) days += 304 + pieces[1];//31+28+31+30+31+30+31+31+30+31;
        else if(pieces[2]==12) days += 334 + pieces[1];//31+28+31+30+31+30+31+31+30+31+30;

        unsigned long long time = 0;
        time = days*86400000 + pieces[3]*31536000000 + pieces[4]*3600000 + pieces[5]*60000 + pieces[6];

        Sense data(pieces[0],time);

        for(int i = 0; i < 10; i++){
            data.addSensors(i, pieces[7 + i]);
        }
        senses.push_back(data);
    }
    file.close();//Close file to avoid read/write error

    //^^Done reading in UDPs from file now^^


    //Turning UDP data into entries/exits/peeks:

    for(int i = 0; i < senses.size() - 1; i++){
        unsigned int lastCheck = i;
        while(lastCheck < senses.size() && senses.at(i+1).getTime() - senses.at(i).getTime() < threshold){
            lastCheck++;
        }//find how many udps are in the threshold
        //(increases efficiency by not having to do these checks 80 times)

        for(unsigned short int b = 0; b < 10; b++){//for every board
            for(unsigned short int s = 1; s <= 8; s++){//for every sensor
                if(senses.at(i).getSensor(b, s) == 1){//if a gate is activated here
                    unsigned int found = lastCheck+1;// -1?

                    for(unsigned int n = i+1; n <= lastCheck; n++){//skipped over if lastCheck == i
                        if(senses.at(n).getSensor(b,9-s) == 1){//if there is a corresponding gate match
                            found = n;//first possibility is i+1, last possibility is lastCheck
                            if(s<9-s){//if exit, like 2 (inner) then 7 (outer)
                                Event e(senses.at(i).getHiveID(), senses.at(i).getTime(), "Exit");
                                events.push_back(e);
                            }
                            else{//else entry, like 7 (outer) then 2 (inner)
                                Event e(senses.at(i).getHiveID(), senses.at(i).getTime(), "Entry");
                                events.push_back(e);
                            }
                            break;
                        }
                    }

                    for(unsigned int n = i+1; n < found; n++){//up until found, remove the former senses
                        senses.at(n).setSensor(b,s,0);
                    }
                    if(found != lastCheck+1){//if found still equals lastCheck+1 (equivalently, if not exit or entry), peek
                                             //remove all consecutive latter senses starting at found
                        unsigned int n = found;
                        while(n < senses.size() && senses.at(n).getSensor(b,9-s) == 1){
                            senses.at(n).setSensor(b,9-s,0);
                            n++;
                        }
                    }
                    else{
                        Event e(senses.at(i).getHiveID(), senses.at(i).getTime(), "Peek");
                        events.push_back(e);
                    }
                }
            }
        }

    }


    for(unsigned long long i = 0; i < events.size(); i++){
        std::cout << events.at(i).toString() <<std::endl;
    }



    return 0;
}
