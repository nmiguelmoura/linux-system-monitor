#include "process_parser.h"

std::string ProcessParser::getCmd(std::string pid) {
    std::string path = Path::basePath() + pid + Path::cmdPath();
    std::string line = Utils::getFirstLineFromFileStream(path);
    return line;
}

std::vector<std::string> ProcessParser::getPidList() {
    DIR* dir;
    std::vector<std::string> list {};
    
    if(!(dir = opendir("/proc"))) {
        throw std::runtime_error(std::strerror(errno));
    }

    while(dirent* dirp = readdir(dir)) {
        // Check if its a directory.
        if(dirp->d_type != DT_DIR) {
            // If not a directory, continue to next one.
            continue;
        }

        if (all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c){ return std::isdigit(c); })) {
            list.push_back(dirp->d_name);
        }
    }

    if(closedir(dir)) {
        throw std::runtime_error(std::strerror(errno));
    }

    return list;
}

std::string ProcessParser::getVmSize(std::string pid) {
    std::string path = Path::basePath() + pid + Path::statusPath();
    std::string line = Utils::getLineFromStreamByKeyName("VmData", path);
    std::vector<string> words = Utils::getWordsFromLine(line, 9);
    std::string vmSize = words[1];
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
    std::string path = Path::basePath() + pid + Path::statusPath();
    std::string line = Utils::getLineFromStreamByKeyName("Uid", path);
    std::vector<string> words  = Utils::getWordsFromLine(line, 9);
    std::string user_id = words[1];

    std::string key_name = "x:" + user_id;
    path = Path::etcPasswd();
    std::ifstream stream = Utils::getStream(path);
    std::string user_name = "";
    while(std::getline(stream, line)) {
        if(line.find(key_name) != std::string::npos) {
            user_name = line.substr(0, line.find(":"));
            break;
        }
    }

    return user_name;
}

int ProcessParser::getNumberOfCores() {
    std::string path = Path::basePath() + Path::cpuInfo();
    std::string line = Utils::getLineFromStreamByKeyName("cpu cores", path);
    std::vector<std::string> words = Utils::getWordsFromLine(line, 32);
    int cpu_cores = stoi(words[2]);
    return cpu_cores;
}