#include <iostream>
#include "day01.h"
#include "util.h"


/* PART ONE

void run_day01() {
    std::cout << "Running Day 01..." << std::endl;
    std::string path = "../data/day01.txt";
    std::vector<std::string> lines = read_lines(path);
    int zeroCount = 0;
    int currNum = 50;

    for(size_t i = 0; i < lines.size(); i++){
        char direction = lines[i][0];
        std::string number_part = lines[i].substr(1);
        int num = std::stoi(number_part);


        if(direction == 'R'){
            currNum = (currNum + num) % 100;
        } else{
            currNum = (currNum - num + 100) % 100;
        }
        if(currNum == 0){
            zeroCount++;
        }

    }

    std::cout << "The dial reached zero "  << zeroCount << " times.";
}

*/

void run_day01() {
    std::cout << "Running Day 01..." << std::endl;
    std::string path = "../data/day01.txt";
    std::vector<std::string> lines = read_lines(path);
    int zeroCount = 0;
    int currNum = 50;

    for(size_t i = 0; i < lines.size(); i++){
        char direction = lines[i][0];
        std::string number_part = lines[i].substr(1);
        int num = std::stoi(number_part);
        int rounds = num / 100;
        zeroCount += rounds;
        int rest = num - (100 * rounds);


        if(direction == 'R'){
            if(currNum + rest >= 100){
                zeroCount++;
            }
            currNum = (currNum + rest) % 100;
            
        } else{
            if(currNum - rest <= 0 && currNum != 0){ // 0 to -1 also counted as one otherwise
                zeroCount++;
            }
            currNum = (currNum - rest + 100) % 100;
        }

    }

    std::cout << "The dial reached zero "  << zeroCount << " times.";
}