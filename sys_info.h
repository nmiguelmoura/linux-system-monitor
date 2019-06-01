#pragma once

#include <iostream>
#include <string>
#include <vector>

class SysInfo {
    private:
        std::vector<std::string> last_cpu_stats;
        std::vector<std::string> current_cpu_stats;
        std::vector<std::string> cores_stats;
        std::vector<std::vector<std::string>> last_cpu_cores_stats;
        std::vector<std::vector<std::string>> current_cpu_cores_stats;
        std::string cpu_percent;
        float mem_percent;
        std::string os_name;
        std::string kernel_ver;
        long up_time;
        int total_proc;
        int running_proc;
        int threads;
    public:
        SysInfo();
        void setAttributes();
        void setLastCpuMeasures();
        std::string getMemPercent() const;
        long getUptime() const;
        std::string getThreads() const;
        std::string getTotalProc() const;
        std::string getRunningProc() const;
        std::string getKernelVersion() const;
        std::string getOSName() const;
        std::string getCpuPercent() const;
        void getOtherCores(int size) const;
        void setCpuCoreStats();
        std::vector<std::string> getCoreStats() const;

};