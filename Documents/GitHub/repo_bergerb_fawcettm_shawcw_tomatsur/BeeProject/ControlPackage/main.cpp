#include <iostream>

#include <string>
#include <bitset>
#include <vector>
#include <fstream>

#include "sense.h"
#include "event.h"
#include "decoder.h"
#include "udpmessage.h"
#include "controller.h"
#include "eventcontainer.h"

int main()
{
    /*
     * START
     * OF MAIN METHOD FOR DELIVERABLE 3
     */

//    Decoder d("../output.txt");
//    temp = d.decode(); numUDPs.push_back(temp.at(0)); uppers.push_back(temp.at(1)); lowers.push_back(temp.at(2));

    /*
     * END
     * OF MAIN METHOD FOR DELIVERABLE 3
     *
     * Comment out everything below if not already done
     */

//    std::bitset<8> test[2];
//    for(int i = 0; i < test->size(); i++){
//        for(int k = 0; k < test[i].size(); k++){
//            std::cout <<i <<" " <<k <<std::endl;
//        }
//    }

//    std::vector<std::bitset<8>> test;
//    for(int i = 0; i < 10; i++){
//        std::bitset<8> temp;
//        test.push_back(temp);
//        for(int k = 0; k < 8; k++){
//            if(k % 2 == 0 )
//                test.at(i)[k] = 0;
//            else test.at(i)[k] = 1;
//        }
//    }
//    for(int i = 0; i < test.size(); i++){
//        for(int k = 0; k < test.at(i).size(); k++){
//            std::cout <<i <<" " <<k <<std::endl;
//        }
//    }






//    for(int i = 5; i < -1; i++)
//        std::cout <<"huh";



    std::vector<int> numUDPs;
    std::vector<int> uppers;
    std::vector<int> lowers;

    std::vector<int> temp;

//    // 4500 Chunks!!!!!!!!!!!! 222

    std::chrono::system_clock::time_point t;
    t += std::chrono::milliseconds(1546300800000);
    UDPMessage m;
    m.generate_random(20398, "0097", t, "winter", 60, "robbery", 4500);

    int hiveID = 1000;

    for(int i = 0; i < 11; i++){
        m.generate_random(424, to_string(hiveID), t, "winter", 60+5*i, "normal", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "winter", 60+5*i, "swarm", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "winter", 60+5*i, "robbery", 4500);
        hiveID++;
    }
    for(int i = 0; i < 11; i++){
        m.generate_random(424, to_string(hiveID), t, "fall", 60+5*i, "normal", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "fall", 60+5*i, "swarm", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "fall", 60+5*i, "robbery", 4500);
        hiveID++;
    }
    for(int i = 0; i < 11; i++){
        m.generate_random(424, to_string(hiveID), t, "summer", 60+5*i, "normal", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "summer", 60+5*i, "swarm", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "summer", 60+5*i, "robbery", 4500);
        hiveID++;
    }
    for(int i = 0; i < 11; i++){
        m.generate_random(424, to_string(hiveID), t, "spring", 60+5*i, "normal", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "spring", 60+5*i, "swarm", 4500);
        hiveID++;
        m.generate_random(424, to_string(hiveID), t, "spring", 60+5*i, "robbery", 4500);
        hiveID++;
    }




//    //seed 222 used for model generating
//    std::ofstream file("../dataCollector.txt");
//    for(int i = 0; i < numUDPs.size(); i++){
//        file <<numUDPs.at(i) <<std::endl;
//    }
//    file <<std::endl;
//    for(int i = 0; i < uppers.size(); i++){
//        file <<uppers.at(i) <<std::endl;
//    }
//    file <<std::endl;
//    for(int i = 0; i < lowers.size(); i++){
//        file <<lowers.at(i) <<std::endl;
//    }
//    file.close();





//    std::vector<double> aLevels;

//    for(int i = 0; i < 4; i++){
//        for(int k = 0; k < 11; k++)
//            aLevels.push_back( ( ((1 + i*0.2) * (60+5*k)) - 55) / 121);
//    }
//    std::sort(aLevels.begin(), aLevels.end());

//    for(int i = 0; i < aLevels.size(); i++)
//        std::cout <<aLevels.at(i) <<std::endl;


    /*
     * Testing simulation
     */
//    UDPMessage m;

//    std::default_random_engine gen;

//    double lowerBound2 = 0;
//    double upperBound2 = 0.9999;
//    std::uniform_real_distribution<double> eventTypeDist(lowerBound2,upperBound2);
//    double type = eventTypeDist(gen);

//    std::vector<std::vector<int>> sensors;
//    for(int s = 0; s < 10; s++){
//        std::vector<int> temp;
//        sensors.push_back(temp);
//    }

//    type = eventTypeDist(gen);

//    std::chrono::system_clock::time_point t;
//    t += std::chrono::milliseconds(1546300800000);

//    for(int b = 0; b < 10; b++){
//        std::cout <<"start"<<std::endl;
//        std::vector<int> entryPossibilities;
//        entryPossibilities.push_back(5); entryPossibilities.push_back(6);
//        entryPossibilities.push_back(7); entryPossibilities.push_back(8);
//        for(int e = 0; e < 4; e++){
//            int index = (int)(type*entryPossibilities.size());
//            std::cout <<index<<std::endl;
//            sensors.at(b).push_back( entryPossibilities[index] );
//            entryPossibilities.erase(entryPossibilities.begin() + index);
//            type = eventTypeDist(gen);
//        }
//    }



    return 0;
}
