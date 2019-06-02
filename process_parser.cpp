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

    if(line != "") {
        std::vector<string> words = Utils::getWordsFromLine(line, 9);
        std::string vmSize = words[1];
        return std::to_string(stof(vmSize) / float(1024));
    }

    return "0";
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

std::vector<std::string> ProcessParser::getSysCpuPercent(std::string coreNumber) {
    std::string path = Path::basePath() + Path::statPath();
    std::string line = Utils::getLineFromStreamByKeyName("cpu" + coreNumber, path);
    std::vector<std::string> words = Utils::getWordsFromLine(line);
    return words;
};

float ProcessParser::getSysActiveCpuTime(std::vector<std::string> values) {
    return(
        stof(values[(int)CPUStates::S_USER]) + 
        stof(values[(int)CPUStates::S_NICE]) +
        stof(values[(int)CPUStates::S_SYSTEM]) +
        stof(values[(int)CPUStates::S_IRQ]) +
        stof(values[(int)CPUStates::S_SOFTIRQ]) +
        stof(values[(int)CPUStates::S_STEAL]) + 
        stof(values[(int)CPUStates::S_GUEST]) +
        stof(values[(int)CPUStates::S_GUEST_NICE])
    );
}

float ProcessParser::getSysIdleCpuTime(std::vector<std::string> values) {
    return(
        stof(values[(int)CPUStates::S_IDLE]) + 
        stof(values[(int)CPUStates::S_IOWAIT])
    );
}

float ProcessParser::getSysRamPercent() {
    std::string path = Path::basePath() + Path::memInfoPath();
    
    // Total mem
    std::string line = Utils::getLineFromStreamByKeyName("MemAvailable", path);
    std::vector<std::string> words = Utils::getWordsFromLine(line, 32);
    float total_mem = stof(words[1]);

    // Free mem
    line = Utils::getLineFromStreamByKeyName("MemFree", path);
    words = Utils::getWordsFromLine(line, 32);
    float free_mem = stof(words[1]);

    // Buffers
    line = Utils::getLineFromStreamByKeyName("Buffers", path);
    words = Utils::getWordsFromLine(line, 32);
    float buffers = stof(words[1]);

    return float(100.0 * (1 - (free_mem / (total_mem - buffers))));
}

std::string ProcessParser::getSysKernelVersion() {
    std::string path = Path::basePath() + Path::versionPath();
    std::string line = Utils::getFirstLineFromFileStream(path);
    std::vector<std::string> words = Utils::getWordsFromLine(line);
    return words[2];
}

int ProcessParser::getTotalThreads() {
    int threads = 0;
    std::string path;
    std::string line;
    std::vector<std::string> words;
    std::vector<std::string> pid_list = ProcessParser::getPidList();
    for(int a = 0; a < pid_list.size(); a++) {
        path = Path::basePath() + pid_list[a] + Path::statusPath();
        line = Utils::getLineFromStreamByKeyName("Threads", path);
        words = Utils::getWordsFromLine(line, 9);
        threads += stoi(words[1]);
    }

    return threads;
}

int ProcessParser::getTotalNumberOfProcesses() {
    std::string path = Path::basePath() + Path::statPath();
    std::string line = Utils::getLineFromStreamByKeyName("processes", path);
    std::vector<std::string> words = Utils::getWordsFromLine(line, 32);
    return stoi(words[1]);
}

int ProcessParser::getNumberOfRunningProcesses() {
    std::string path = Path::basePath() + Path::statPath();
    std::string line = Utils::getLineFromStreamByKeyName("procs_running", path);
    std::vector<std::string> words = Utils::getWordsFromLine(line, 32);
    return stoi(words[1]);
}

int ProcessParser::getNumberOfCores() {
    std::string path = Path::basePath() + Path::cpuInfo();
    std::string line = Utils::getLineFromStreamByKeyName("cpu cores", path);
    std::vector<std::string> words = Utils::getWordsFromLine(line, 32);
    int cpu_cores = stoi(words[2]);
    return cpu_cores;
}

std::string ProcessParser::getOSName() {
    std::string path = Path::osInfo();
    std::string line = Utils::getLineFromStreamByKeyName("PRETTY_NAME", path);

    // 61 is dec for =.
    std::vector<std::string> words = Utils::getWordsFromLine(line, 61);
    std::string os_name = words[1];
    os_name.erase(std::remove(os_name.begin(), os_name.end(), '"'), os_name.end());
    return os_name;
}

std::string ProcessParser::printCpuStats(std::vector<std::string> values1, std::vector<std::string> values2) {
    float active_time = ProcessParser::getSysActiveCpuTime(values2) - ProcessParser::getSysActiveCpuTime(values1);
    float idle_time = ProcessParser::getSysIdleCpuTime(values2) - ProcessParser::getSysIdleCpuTime(values1);
    float total_time = active_time + idle_time;
    float result = (active_time / total_time) * 100.0;
    return std::to_string(result);
}