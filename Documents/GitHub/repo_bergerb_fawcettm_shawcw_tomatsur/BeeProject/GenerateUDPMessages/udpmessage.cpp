#include "udpmessage.h"

UDPMessage::UDPMessage()
{

}

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
   // send_to_db(message, std::stoi(hiveId), ms.count()); //uncomment this to put generated messages into the database
    return message;
}

void UDPMessage::generate_random(int seed){ //generate random UDP messages
    read_file("activityLevels.txt");
    std::default_random_engine gen;
    gen.seed(seed); //seed the generator
    std::ofstream file("../output.txt");

    int prev = -50;
    for(int i = 0; i < 500; i++){
        prev += 50;
        queue.push(prev);
    }

    double lsize = 500.0 / lambda.size();

    std::chrono::system_clock::time_point base = std::chrono::system_clock::now();
    std::chrono::system_clock::duration dur = base.time_since_epoch();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
    int lastNum = 50 - std::stoi(std::to_string(ms.count()).substr(std::to_string(ms.count()).size() - 2, 2));
    std::chrono::milliseconds milli = std::chrono::milliseconds(lastNum);

    base += milli;

    int s = queue.size();
    for(int i = 0; i < s; i++){
        bool noActivity = true;
        std::vector<std::vector<int>> v;
        int act = lambda.at(i / lsize);
       // std::cout << i << std::endl;
        for(int k = 0; k < 10; k++){ //generate activity on different boards
            std::vector<int> sens;
            if ((gen() % (25 - act)) == 1){
                noActivity = false;
                for(int j = 0; j < 8; j++){
                    if(gen() % 6 == 1){
                        sens.push_back(j);
                    }
                }
            }
            v.push_back(sens);
        }

        unsigned int wait = queue.top();
        queue.pop();
        if(!noActivity){
            std::string out = generate("0012", base + std::chrono::milliseconds(wait), v); //generate the message
            //std::cout << out << std::endl;
            file << out << std::endl;
        }
    }
    file.close();
    DBTool *dbtool = new DBTool("../HiveTableDB");
    DBHive *ext = new DBHive(dbtool, "HiveTable");
    ext->select_all();
    std::cout << ext->list->to_string() << std::endl;
   // std::cout << "finished" << std::endl;
}

void UDPMessage::read_file(std::string filename){
    std::ifstream file(filename); //open the file
    if(!file){
        std::cerr << "File is not open" << std::endl;
    }
    else{
        while(!file.eof()){ //while there is still text left to be read,
            int input;
            file >> input;
            lambda.push_back(input); //store it in lambda
        }
    }
    file.close();
}

void UDPMessage::send_to_db(std::string msg, int hid, unsigned long long time){
    DBTool *dbtool = new DBTool("../HiveTableDB");
    DBHive *ext = new DBHive(dbtool, "HiveTable");
    ext->add_row(ext->size() + 1, hid, msg, time);
}
