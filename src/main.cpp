#include <iostream>
#include "day01.h"
#include "day02.h"
int main(int argc, char* argv[]){
    std::cout << "Advent of Code 2025\n";
    
    if(argc < 2){
        std::cerr << "Usage: ./aoc <dayxx>\n";
        return 1;
    }

    int day = std::stoi(argv[1]);
    switch (day)
    {
        case 1: run_day01();
        break;
        case 2: run_day02();
        break;
    default:
        std::cerr << "Unkown day\n";
    }
}