#include "day02.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>

bool isInvalidID(long long id) {
    std::string s = std::to_string(id);
    int n = s.size();

    if (n % 2 != 0) return false;       // must be even length

    int half = n / 2;

    return s.substr(0, half) == s.substr(half, half);
}

bool isInvalidID2(long long id) {
    std::string s = std::to_string(id);
    int n = s.size();

    // try all possible partition lengths from 1 to n/2
    for (int len = 1; len <= n / 2; len++) {
        if (n % len != 0) continue;  // must divide evenly

        bool repeating = true;

        for (int j = 0; j + len < n; j += len) {
            if (s.substr(j, len) != s.substr(j + len, len)) {
                repeating = false;
                break;
            }
        }

        if (repeating) {
            return true;  
        }
    }

    return false;  // valid, no repetition
}


//PART 1,2
void run_day02(){
    std::cout <<"Running Day 02" << std::endl;
    std::string path ="../data/day02.txt";

    std::vector<std::string> lines = read_lines(path); //has only a string
    
    std::stringstream ss(lines[0]);
    std::string segment;
    std::vector<std::string> parts;
    long long sum = 0;

    while(std::getline(ss, segment, ',')){
        parts.push_back(segment);
    }

    for(int i = 0; i < parts.size(); i++){
        std::stringstream ss(parts[i]);
        std::string firstHalf;
        std::string secondHalf;
        std::getline(ss, firstHalf, '-');
        std::getline(ss, secondHalf);

        long long start = std::stoll(firstHalf);
        long long end = std::stoll(secondHalf);

        for(long long j = start; j <= end; j++){
            if(isInvalidID2(j)){
                sum+=j;
            }
        }

    }

    std::cout << "The sum of all invalid IDS is " << sum << "!";

}
