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

long long applyOp(long long a, char op, long long b){
    switch (op)
    {
    case '*': return a * b;
    case '+': return a + b;
    default:
        break;
    } 
    throw std::runtime_error("Invalid operator");
}

double getDistance3D(const Point3D& a, const Point3D& b){
    double d_x = b.x - a.x;
    double d_y = b.y - a.y;
    double d_z = b.z - a.z;

    return std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);
}
