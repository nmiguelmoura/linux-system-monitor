#include "sys_info.h"
#include "process_parser.h"

SysInfo::SysInfo() {
    this->getOtherCores(ProcessParser::getNumberOfCores());
    this->setLastCpuMeasures();
    this->setAttributes();
    this->os_name = ProcessParser::getOSName();
    this->kernel_ver = ProcessParser::getSysKernelVersion();
}

void SysInfo::setAttributes() {
    this->mem_percent = ProcessParser::getSysRamPercent();
    this->up_time = ProcessParser::getSysUpTime();
    this->total_proc = ProcessParser::getTotalNumberOfProcesses();
    this->running_proc = ProcessParser::getNumberOfRunningProcesses();
    this->threads = ProcessParser::getTotalThreads();
    this->current_cpu_stats = ProcessParser::getSysCpuPercent();
    this->cpu_percent = ProcessParser::printCpuStats(this->last_cpu_stats, this->current_cpu_stats);
    this->last_cpu_stats = this->current_cpu_stats;
    this->setCpuCoresStats();
}

void SysInfo::setLastCpuMeasures() {
    this->last_cpu_stats = ProcessParser::getSysCpuPercent();
}

std::string SysInfo::getMemPercent() const {
    return std::to_string(this->mem_percent);
}

long SysInfo::getUptime() const {
    return up_time;
}

std::string SysInfo::getThreads() const {
    return std::to_string(this->threads);
}

std::string SysInfo::getTotalProc() const {
    return std::to_string(this->total_proc);
}

std::string SysInfo::getRunningProc() const {
    return std::to_string(this->running_proc);
}

std::string SysInfo::getKernelVersion() const {
    return this->kernel_ver;
}

std::string SysInfo::getOSName() const {
    return this->os_name;
}

std::string SysInfo::getCpuPercent() const {
    return this->cpu_percent;
}

void SysInfo::getOtherCores(int size) {
    this->cores_stats = std::vector<std::string>();
    this->cores_stats.resize(size);
    
    this->last_cpu_cores_stats = std::vector<std::vector<std::string>>();
    this->last_cpu_cores_stats.resize(size);

    this->current_cpu_cores_stats = std::vector<std::vector<std::string>>();
    this->current_cpu_cores_stats.resize(size);

    for(int a = 0; a < size; a++) {
        this->last_cpu_cores_stats[a] = ProcessParser::getSysCpuPercent(std::to_string(a));
    }

}

void SysInfo::setCpuCoresStats() {
    for(int a = 0; a < this->current_cpu_cores_stats.size(); a++) {
        this->current_cpu_cores_stats[a] = ProcessParser::getSysCpuPercent(std::to_string(a));
    }

    for(int a = 0; a < this->current_cpu_cores_stats.size(); a++) {
        this->cores_stats[a] = ProcessParser::printCpuStats(this->last_cpu_cores_stats[a], this->current_cpu_cores_stats[a]);
    }

    this->last_cpu_cores_stats = this->current_cpu_cores_stats;
}

std::vector<std::string> SysInfo::getCoreStats() const {
    std::vector<std::string> result = {};

    for(int a = 0; a < this->cores_stats.size(); a++) {
        std::string temp = "cpu" + std::to_string(a) + ": ";
        float check = stof(this->cores_stats[a]);

        if(!check || this->cores_stats[a] == "nan") {
            return std::vector<std::string>();
        }

        temp += Utils::getProgressbar(this->cores_stats[a]);
        result.push_back(temp);
    }

    return result;
}