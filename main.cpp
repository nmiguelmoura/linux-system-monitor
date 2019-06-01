#include <iostream>
#include <string>
#include <cstring>
#include "constants.h"
#include "utils.h"
#include "process_parser.h"
#include "sys_info.h"

int main() {

    // Print /proc/ directory contents.
    // std::cout << "Hello, World!" << std::endl;
    // std::cout << "listing: " << Path::basePath() << std::endl;
    // std::string command = "ls " + Path::basePath();
    // int n = command.length();
    // char char_command[n+1];
    // strcpy(char_command, command.c_str());
    // std::system(char_command);

    // std::cout << Utils::getProgressbar("0%") << std::endl;
    // std::cout << Utils::convertToTime(3665) << std::endl;
    // std::cout << Utils::padStart("2", 10, ".") << std::endl;

    std::string pid = "2556";
    std::cout << "VmData: " << ProcessParser::getVmSize(pid) << " Mb" << std::endl;
    std::cout << "Cpu percentage: " << ProcessParser::getCpuPercent(pid) << "%" << std::endl;
    std::cout << "Process Up Time: " << ProcessParser::getProcUpTime(pid) << std::endl;
    std::cout << "Sys Up Time: " << ProcessParser::getSysUpTime() << std::endl;
    std::cout << "Proc user: " << ProcessParser::getProcUser(pid) << std::endl;
    
    std::cout << "\nPID List:" << std::endl;
    int count = 0;
    std::vector<std::string> pidList = ProcessParser::getPidList();
    for(auto a : pidList) {
        std::cout << a << " ";

        count++;

        if(count == 10) {
            std::cout << std::endl;
            count = 0;
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Cmd: " << ProcessParser::getCmd(pid);
    std::cout << std::endl;
    std::cout << "CPU cores: " << ProcessParser::getNumberOfCores() << std::endl;

    std::cout << std::endl;

    std::cout << "core0:" << std::endl;
    std::vector<std::string> core0 = ProcessParser::getSysCpuPercent("0");
    for(auto a : core0) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Sys Active CPU Time (core0): " << ProcessParser::getSysActiveCpuTime(core0) << std::endl;
    std::cout << "Sys Idle CPU Time (core0): " << ProcessParser::getSysIdleCpuTime(core0) << std::endl;
    std::cout << "Sys Ram Percent: " << ProcessParser::getSysRamPercent() << std::endl;
    std::cout << "Kernel Version: " << ProcessParser::getSysKernelVersion() << std::endl;
    std::cout << "OS Name: " << ProcessParser::getOSName() << std::endl;
    std::cout << "Threads: " << ProcessParser::getTotalThreads() << std::endl;
    std::cout << "Total Processes: " << ProcessParser::getTotalNumberOfProcesses() << std::endl;
    std::cout << "Running Processes: " << ProcessParser::getNumberOfRunningProcesses() << std::endl;


    SysInfo sys;


    return 0;
}