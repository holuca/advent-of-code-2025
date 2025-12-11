#include <iostream>
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
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
        case 3: run_day03();
        break;
        case 4: run_day04();
        break;
        case 5 : run_day05();
        break;
        case 6 : run_day06();
        break;
        case 7 : run_day07();
        break;
        case 8 : run_day08();
        break;
        case 9 : run_day09();
        break;
        case 10 : run_day10();
        break;
        case 11 : run_day11();
        break;
        case 12 : run_day12();
        break;

    default:
        std::cerr << "Unkown day\n";
    }
}