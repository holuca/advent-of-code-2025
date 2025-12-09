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

long long getSurface(const Coord2D& c1, const Coord2D& c2) {
    long long width  = std::llabs((long long)c1.x - (long long)c2.x) + 1;
    long long height = std::llabs((long long)c1.y - (long long)c2.y) + 1;
    return width * height;
}
