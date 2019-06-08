#include "processContainer.h"
#include "processParser.h"

ProcessContainer::ProcessContainer() {
    this->refreshList();
}

void ProcessContainer::refreshList() {
    this->list.clear();
    std::vector<std::string> pidList = ProcessParser::getPidList();

    for(int a = 0; a < pidList.size(); a++) {
        Process p(pidList[a]);
        list.push_back(p);
    }
}

std::string ProcessContainer::printList() {
    std::string result = "";
    for(int a = 0; a < this->list.size(); a++) {
            result += this->list[a].getProcess();
            result += "\n";
    }
    return result;
}

std::vector<std::string> ProcessContainer::getList() {
    std::vector<std::string> values = {};
    for(int a = (list.size() - 10); a < this->list.size(); a++) {
        values.push_back(this->list[a].getProcess());
    }
    return values;
}