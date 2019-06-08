#include "process.h"
#include "processParser.h"
#include "utils.h"
#include "constants.h"

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
    if(!ProcessParser::isPidExisting(this->pid)) {
        return "";
    }

    return (
        Utils::resizeString(this->pid)
        + Utils::resizeString(this->user, ParameterSize::userSize())
        + Utils::resizeString(this->mem)
        + Utils::resizeString(this->cpu)
        + Utils::resizeString(this->up_time)
        + Utils::resizeString(this->cmd, ParameterSize::cmdSize())
    );
}