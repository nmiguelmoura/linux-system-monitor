#include "process_parser.h"
#include <typeinfo>

std::string ProcessParser::getVmSize(std::string pid) {
    std::string key_name = "VmData";
    std::string path = Path::basePath() + pid + Path::statusPath();
    std::ifstream stream = Utils::getStream(path);
    
    std::string vmSize = "0";
    std::string line;
    std::vector<string> words {};
    while(std::getline(stream, line)) {
        if(line.compare(0, key_name.size(), key_name) == 0) {
            words = Utils::getWordsFromLine(line, 9);
            vmSize = words[1];
            break;
        }
    }

    return std::to_string(stof(vmSize) / float(1024));
}

std::string ProcessParser::getCpuPercent(std::string pid) {
    std::string path = Path::basePath() + pid + Path::statPath();
    std::string line = Utils::getFirstLineFromFileStream(path);
    std::vector<std::string> words = Utils::getWordsFromLine(line);

    float uTime = stof(ProcessParser::getProcUpTime(pid));
    float sTime = stof(words[14]);
    float cuTime = stof(words[15]);
    float csTime = stof(words[16]);
    float startTime = stof(words[21]);
    float upTime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float totalTime = uTime + sTime + cuTime + csTime;
    float seconds = upTime - (startTime / freq);
    float result = 100 * ((totalTime / freq) / seconds);

    return std::to_string(result);
}

long int ProcessParser::getSysUpTime() {
    std::string path = Path::basePath() + Path::upTimePath();
    std::string line = Utils::getFirstLineFromFileStream(path);
    std::vector<std::string> words = Utils::getWordsFromLine(line);

    return stoi(words[0]);
}

std::string ProcessParser::getProcUpTime(std::string pid) {
    std::string path = Path::basePath() + pid + Path::statPath();
    std::string line = Utils::getFirstLineFromFileStream(path);
    std::vector<std::string> words = Utils::getWordsFromLine(line);
    
    return std::to_string(stof(words[13]) / sysconf(_SC_CLK_TCK));
}

std::string ProcessParser::getProcUser(std::string pid) {
    std::string key_name = "Uid";
    std::string path = Path::basePath() + pid + Path::statusPath();
    std::ifstream stream = Utils::getStream(path);

    std::string user_id = "0";
    std::string line;
    std::vector<string> words {};
    while(std::getline(stream, line)) {
        if(line.compare(0, key_name.size(), key_name) == 0) {
            words = Utils::getWordsFromLine(line, 9);
            user_id = words[1];
            break;
        }
    }

    key_name = "x:" + user_id;
    path = Path::etcPasswd();
    stream = Utils::getStream(path);
    std::string user_name = "";
    while(std::getline(stream, line)) {
        if(line.find(key_name) != std::string::npos) {
            user_name = line.substr(0, line.find(":"));
            break;
        }
    }

    return user_name;
}