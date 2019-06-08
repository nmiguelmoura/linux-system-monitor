#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include "constants.h"
#include "utils.h"
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>

class ProcessParser {
    public:
        static std::string getCmd(std::string pid);
        static std::vector<std::string> getPidList();
        static std::string getVmSize(std::string pid);
        static std::string getCpuPercent(std::string pid);
        static long int getSysUpTime();
        static std::string getProcUpTime(std::string pid);
        static std::string getProcUser(std::string pid);
        static std::vector<std::string> getSysCpuPercent(std::string coreNumber = "");
        static float getSysActiveCpuTime(std::vector<std::string> values);
        static float getSysIdleCpuTime(std::vector<std::string> values);
        static float getSysRamPercent();
        static std::string getSysKernelVersion();
        static int getTotalThreads();
        static int getTotalNumberOfProcesses();
        static int getNumberOfRunningProcesses();
        static int getNumberOfCores();
        static std::string getOSName();
        static std::string printCpuStats(std::vector<std::string> values1, std::vector<std::string> values2);
        static bool isPidExisting(std::string pid);
};