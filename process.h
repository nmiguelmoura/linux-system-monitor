#pragma once
#include <iostream>
#include <string>

class Process {
    private:
        std::string pid;
        std::string user;
        std::string cmd;
        std::string cpu;
        std::string mem;
        std::string up_time;
    public:
        Process(std::string pid);
        void setPid(std::string pid);
        std::string getPid() const {
            return this->pid;
        };
        std::string getUser() const {
            return this->user;
        };
        std::string getCmd() const {
            return this->cmd;
        };
        std::string getCpu() const {
            return this->cpu;
        };
        std::string getMem() const {
            return this->mem;
        };
        std::string getUpTime() const {
            return this->up_time;
        };
        std::string getProcess();

};