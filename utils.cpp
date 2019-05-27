#include "utils.h"

std::string Utils::padStart(std::string _value, int _width = 2, std::string _symbol = "0") {
    short int value_length = _value.length();
    if(value_length < _width) {
        short int diff = _width - value_length;
        std::string pad = "";

        for(short int a = 0; a < diff; a++) {
            pad += _symbol;
        }

        return pad + _value;   
    }

    return _value;
}

std::string Utils::convertToTime(long int _input_seconds) {
    long minutes = _input_seconds / 60;
    long hours = minutes / 60;
    minutes = int(minutes % 60);
    long seconds = int(_input_seconds % 60);

    return Utils::padStart(std::to_string(hours)) + ":" + Utils::padStart(std::to_string(minutes)) + ":" + Utils::padStart(std::to_string(seconds));
}

std::string Utils::getProgressbar(std::string _percent) {
    std::string result = "0% ";
    short int width = 50;
    float num_of_bars = (stof(_percent) / 100) * width;

    for(short int a = 0; a < width; a++) {
        if(a < num_of_bars) {
            result += "|";
        } else {
            result += " ";
        }
    }

    result += " " + _percent + "/100%";
    return result;
}

std::ifstream Utils::getStream(std::string _path) {
    std::ifstream stream(_path);

    if(!stream) {
        throw std::runtime_error("Non existing PID.");
    }

    return stream;
}

std::vector<std::string> Utils::getWordsFromLine(std::string &line, int splitter) {
    std::vector<std::string> words {};
    std::string word = "";

    char char_array[line.length() + 1];
    strcpy(char_array, line.c_str());

    for(auto a : char_array) {
        int ia = (int)a;

        if(ia == splitter) {
            if(word != "") {
                words.push_back(word);
                word = "";
            }
        } else {
            word += a;
        }            
    }

    words.push_back(word);
    return words; 
}

std::string Utils::getFirstLineFromFileStream(std::string path) {
    std::ifstream stream = Utils::getStream(path);
    std::string line;
    std::getline(stream, line);
    return line;
}