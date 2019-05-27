#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

class Utils {
public:
    static std::string padStart(std::string value, int width, std::string padValue);
    static std::string convertToTime(long int input_seconds);
    static std::string getProgressbar(std::string percent);
    static std::ifstream getStream(std::string path);
    static std::vector<std::string> getWordsFromLine(std::string &line, int splitter = 32);
    static std::string getFirstLineFromFileStream(std::string path);
    static std::string getLineFromStreamByKeyName(std::string key_name, std::string path);
};