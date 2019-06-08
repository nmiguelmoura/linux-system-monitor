#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "process.h"

class ProcessContainer {
    private:
        std::vector<Process> list;
    public:
        ProcessContainer();
        void refreshList();
        std::string printList();
        std::vector<std::string> getList();
};