#include "udpmessage.h"


UDPMessage::UDPMessage()
{

}

/*
 * Order of Method Calls:
 * generate_random
 *      reads file
 *      for many times, calls generate -makes 1 UDP
 *          calls send_to_db(...) on each one
 */

std::string UDPMessage::generate(std::string hiveId, std::chrono::system_clock::time_point t, std::vector<std::vector<int>> boards){
    message = "HC";
    message += hiveId;
    message += "-D";

    time_t time = std::chrono::system_clock::to_time_t(t);

    tm utc_tm = *gmtime(&time); //change to utc time

    std::chrono::system_clock::duration tp = t.time_since_epoch();

    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp);

    message += std::to_string(utc_tm.tm_mday);
    message += ".";
    message += std::to_string(utc_tm.tm_mon + 1);
    message += ".";
    message += std::to_string(utc_tm.tm_year + 1900).substr(2, 2);
    message += "T";
    message += std::to_string(utc_tm.tm_hour);
    message += ".";
    message += std::to_string(utc_tm.tm_min);
    message += ".";
    if(utc_tm.tm_sec < 10){
        message += "0";
    }
    message += std::to_string(utc_tm.tm_sec);
    message += std::to_string(ms.count()).substr(std::to_string(ms.count()).size() - 3, 3);
    message += "-";
    for(int i = 0; i < boards.size(); i++){ //boards with no activity
        message += "B";
        int n = 0;
        for(int k = 0; k < boards.at(i).size(); k++){ //calculate the binary value
            n += std::pow(2, boards.at(i).at(k) - 1);
        }
        message += std::to_string(n);

    }
    c.add_activity(std::stoi(hiveId), message, ms.count());
    return message;
}

void UDPMessage::generate_random(int seed, std::string hiveID, std::chrono::system_clock::time_point start, std::string season, int temperature, std::string special, int numChunks){
     c.create_hiveUDP_table(std::stoi(hiveID));

    //generate random UDP messages
    std::default_random_engine gen;
    gen.seed(seed); //seed the generator
    std::ofstream file("../simulationTest.txt");

    /*
     * Setting up activity level and entry/exit probabilities
     */

    double activityLevel = 1.3;//quantity of events

    if(season.compare("winter") == 0) activityLevel = 1;
    else if(season.compare("fall") == 0) activityLevel = 1.2;
    else if(season.compare("summer") == 0) activityLevel = 1.4;
    else if(season.compare("spring") == 0) activityLevel = 1.6;

    activityLevel *= temperature;//(1, 1.2, 1.4, 1.6) * (55 -> 110) = (55 -> 176), (0 -> 121)
        //  divide by 121
        //  rand = make a random number (0,5)
        //  1 + (activityLevel/121)*rand
        //  if > 4, set to 4
    activityLevel -= 55;
    activityLevel /= 121.0;
    double lowerBound1 = 0;
    double upperBound1 = 4.99;
    std::uniform_real_distribution<double> numEventDist(lowerBound1,upperBound1);
    double rand = numEventDist(gen);

    double entryProb = 0.5;//quality, or type, of events
    if(special.compare("swarm") == 0)
        entryProb = 0.25;
    else if(special.compare("robbery") == 0)
        entryProb = 0.75;

    /*
     * Generating UDPs:
     */

    std::chrono::system_clock::time_point t;
    t += std::chrono::milliseconds(1546300800000);// Jan 1st 2019 and 0 milliseconds
    if(season.compare("spring") == 0) t += std::chrono::milliseconds(7776000000);//April 1st
    else if(season.compare("summer") == 0) t += std::chrono::milliseconds(15638400000);//July 1st
    else if(season.compare("fall") == 0) t += std::chrono::milliseconds(23587200000);//October 1st


    double lowerBound2 = 0;
    double upperBound2 = 0.9999;
    std::uniform_real_distribution<double> eventTypeDist(lowerBound2,upperBound2);
    double type = eventTypeDist(gen);

    double lowerBound3 = 0;
    double upperBound3 = 0.9999;
    std::uniform_real_distribution<double> noiseDist(lowerBound3,upperBound3);
    double noiseMaker = noiseDist(gen);

    double lowerBound4 = 0;
    double upperBound4 = 0.9999;
    std::uniform_real_distribution<double> timeDist(lowerBound4,upperBound4);
    double wait = timeDist(gen);

    //First 10%: always normal
    //Middle Part 1, 40%: either swarm, robbery, or normal
    //Middle Part 2, 40%: the opposite, to return to normal population
    //Last 10%: always normal
    int netChange = 0;
    int numEnt = 0;
    int numEx = 0;
    int numNoise = 0;
    int numUDPs = 0;
    int upperLim = 0;
    int lowerLim = 0;

    for(int c = 0; c < numChunks; c++){
        //if(c % 10 == 0)
            //std::cout <<"Current Chunk " <<c <<std::endl;
       // std::cout <<std::endl;

        //Setting up sensors double vector:
        std::vector<std::vector<int>> sensors;
        for(int s = 0; s < 10; s++){
            std::vector<int> temp;
            sensors.push_back(temp);
        }

        bool nonzero = false;

        for(int b = 0; b < 10; b++){//for each board
            //std::cout <<netChange <<", ";
            type = eventTypeDist(gen);
            if(type < activityLevel){
                nonzero = true;
                type = eventTypeDist(gen);
                bool doEntry = false;
                if((c < 0.1*numChunks || c > 0.9*numChunks) && type < 0.5)
                    doEntry = true;
                else if(c >= 0.1*numChunks && c <= 0.5*numChunks){
                    if(special.compare("normal") == 0 && type < 0.5)
                        doEntry = true;
                    else if(special.compare("swarm") == 0 && type < 0.25)
                        doEntry = true;
                    else if(special.compare("robbery") == 0 && type < 0.75)
                        doEntry = true;
                }
                else if(c > 0.5*numChunks && c <= 0.9*numChunks){
                    if(special.compare("normal") == 0 && type < 0.5)
                        doEntry = true;
                    else if(special.compare("swarm") == 0 && type < 0.75)
                        doEntry = true;
                    else if(special.compare("robbery") == 0 && type < 0.25)
                        doEntry = true;
                }

                if(doEntry){//if entry
                    std::vector<int> entryPossibilities;
                    entryPossibilities.push_back(5); entryPossibilities.push_back(6);
                    entryPossibilities.push_back(7); entryPossibilities.push_back(8);

                    int count = 1 + (activityLevel)*rand;
                    if(count > 4) count = 4;

                    netChange += count;
                    if(netChange > upperLim) upperLim = netChange;
                    numEnt += count;

                    rand = numEventDist(gen);//get new numEventDist random number ready
                    for(int e = 0; e < count; e++){
                        type = eventTypeDist(gen);
                        int index = (int)(type*entryPossibilities.size());
                        sensors.at(b).push_back(entryPossibilities.at(index));
                        entryPossibilities.erase(entryPossibilities.begin() + index);
                    }

                }
                else{//else, if exit
                    std::vector<int> exitPossibilities;
                    exitPossibilities.push_back(1); exitPossibilities.push_back(2);
                    exitPossibilities.push_back(3); exitPossibilities.push_back(4);

                    int count = 1 + (activityLevel)*rand;
                    if(count > 4) count = 4;

                    netChange -= count;
                    if(netChange < lowerLim) lowerLim = netChange;
                    numEx += count;

                    rand = numEventDist(gen);//get new numEventDist random number ready
                    for(int e = 0; e < count; e++){
                        type = eventTypeDist(gen);
                        int index = (int)(type*exitPossibilities.size());
                        sensors.at(b).push_back(exitPossibilities.at(index));
                        exitPossibilities.erase(exitPossibilities.begin() + index);
                    }
                }
            }
            type = eventTypeDist(gen);
        }

        /*
         * Printing sensors:
         */
//        for(int r=0; r<sensors.size(); r++){
//            for(int c=0; c<sensors.at(r).size(); c++)
//                std::cout <<sensors.at(r).at(c)<<"  ";
//            std::cout <<std::endl;
//        }
//        std::cout <<"^^^^^NORMAL^^^^^^^^" <<std::endl;

        /*
         * Setting (and if desired, printing) oppoSensors:
         */
        std::vector<std::vector<int>> oppoSensors;
        for(int r = 0; r < sensors.size(); r++){
            std::vector<int> temp;
            oppoSensors.push_back(temp);
            for(int c = 0; c < sensors.at(r).size(); c++){
                oppoSensors.at(r).push_back(9 - sensors.at(r).at(c));
                //std::cout <<oppoSensors.at(r).at(c)<<"  ";
            }
            //std::cout <<std::endl;
        }

        std::vector<std::vector<int>> noise;
        bool happened = false;
        for(int b = 0; b < 10; b++){
            std::vector<int> temp;
            noise.push_back(temp);
            for(int s = 1; s <= 8; s++){
                noiseMaker = noiseDist(gen);
                if(noiseMaker < activityLevel/100){
                    numNoise++;
                    happened = true;
                    noise.at(b).push_back(s);
                }
            }
        }

//        std::cout <<generate(hiveID, t, sensors) <<", ";
//        std::cout <<generate(hiveID, t, noise) <<std::endl;//<<", ";
//        std::cout <<generate(hiveID, t, oppoSensors) <<std::endl;


        wait = timeDist(gen);
        //waits go from 150 to 800 milliseconds
            // (800-150)/50 = 13
        int interMaxWait = 800;
        int interMinWait = 150;
        int interBreakTime = interMinWait + 50 * (int)(wait * (interMaxWait - interMinWait + 50) / 50);

        wait = timeDist(gen);
        int noiseBreakTime = 50 + 50 * (int)(wait * (interBreakTime - 50) / 50);

        std::string shid = "";

        if(nonzero){
            std::string sensorsUDP = generate(hiveID, t, sensors);//first
        }

        t += std::chrono::milliseconds(noiseBreakTime);

        if(happened){
            std::string noiseUDP = generate(hiveID, t, noise);//second
        }
        t += std::chrono::milliseconds(interBreakTime-noiseBreakTime);

        if(nonzero){
            std::string oppoSensorsUDP = generate(hiveID, t, oppoSensors);//third
        }

        int gapMaxWait = 550 + (int)((1 - activityLevel) * 900);
        int gapMinWait = 500;
        wait = timeDist(gen);
        int gapTime = gapMinWait + 50 * (int)(wait * (gapMaxWait - gapMinWait + 50) / 50);

        t += std::chrono::milliseconds(gapTime);



//        file <<"BEG   " << sensorsUDP <<std::endl;//first
//        if(happened)
//            file <<"NOISE " << noiseUDP <<std::endl;//second
//        file <<"END   " << oppoSensorsUDP <<std::endl;//third
//        if(nonzero){
//            numUDPs += 2;
//            file <<sensorsUDP <<std::endl;//first
//            if(happened){
//                numUDPs += 1;
//                file <<noiseUDP <<std::endl;//second
//            }
//            file <<oppoSensorsUDP <<std::endl;//third
//        }


   }//end of for each chunk



//    std::cout <<std::endl;
//    std::cout <<"Net Change: " <<netChange <<std::endl;
//    std::cout <<"Number of Entries: " <<numEnt <<std::endl;
//    std::cout <<"Number of Exits: " <<numEx <<std::endl;
//    std::cout <<"Average Noise per UDP: " <<((double)numNoise)/numChunks <<std::endl;
//    std::cout <<"Number of UDPs: " <<numUDPs <<std::endl;
//    std::cout <<"Upper Limit: " <<upperLim <<std::endl;
//    std::cout <<"Lower Limit: " <<lowerLim <<std::endl;

//    file <<std::endl;
//    file <<"Net Change: " <<netChange <<std::endl;
//    file <<"Number of Entries: " <<numEnt <<std::endl;
//    file <<"Number of Exits: " <<numEx <<std::endl;
//    file <<"Average Noise per UDP: " <<((double)numNoise)/numChunks <<std::endl;
//    file <<"Number of UDPs: " <<numUDPs <<std::endl;
//    file <<"Upper Limit: " <<upperLim <<std::endl;
//    file <<"Lower Limit: " <<lowerLim <<std::endl;

    /*
     * File Writing:
     */

    //std::string out = generate("0063", t, boards); //generate it
    //std::cout << out << std::endl;
	
    //file << out << std::endl;

    //file.close();
    //std::cout << "finished" << std::endl; //finished working
    Decoder* decode = new Decoder();
    decode->decode(stoi(hiveID), season, temperature);
}
