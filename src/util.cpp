#include "util.h"
#include <fstream>


std::vector<std::string> read_lines(const std::string &path){

    std::vector<std::string> lines;
    std::ifstream file(path);

    if(!file.is_open()){
        throw std::runtime_error("Could not open input file: " + path);
    }

    std::string line;
    while(std::getline(file, line)){
        lines.push_back(line);
    }
    return lines;
}



