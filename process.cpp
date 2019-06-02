#include "process.h"
#include "process_parser.h"

Process::Process(std::string pid) {
    this->setPid(pid);
    this->user = ProcessParser::getProcUser(pid);
    this->cmd = ProcessParser::getCmd(pid);
    this->cpu = ProcessParser::getCpuPercent(pid);
    this->mem = ProcessParser::getVmSize(pid);
    this->up_time = ProcessParser::getProcUpTime(pid);
}

void Process::setPid(std::string pid) {
    this->pid = pid;
}

std::string Process::getProcess() {
    return (
        this->pid + "   "
        + this->user + "   "
        + this->mem.substr(0, 5) + "   "
        + this->cpu.substr(0, 5) + "   "
        + this->up_time.substr(0, 5) + "   "
        + this->cmd.substr(0, 30)
    );
}