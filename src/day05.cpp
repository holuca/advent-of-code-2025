#include "day05.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <unordered_set>
#include <algorithm>


//PART 2

void run_day05() {
    std::vector<std::string> input = read_lines("../data/day05.txt");
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> ids;

    bool second_part = false;
    int fresh_count = 0;

    for (const std::string& line : input){
        if(line.empty()){
            second_part = true;
            continue;
        }

        if(!second_part){
            size_t dash = line.find('-');
            long long a = std::stoll(line.substr(0, dash));
            long long b = std::stoll(line.substr(dash + 1));
            if(a > b) std::swap(a, b);
            ranges.push_back({a, b});
        } else {
            ids.push_back(std::stoll(line));
        }
    }
    for (long long id : ids){
        for (auto& [a, b] : ranges){
            if (id >= a && id <= b){
                fresh_count++;
                break;
            }
        }
    }
    //sort using first parit inputs
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long long , long long>> merged;
    merged.push_back(ranges[0]);

    for(auto &r : ranges){
        auto &[last_a, last_b] = merged.back();
        //std::pair<long long, long long>& temp = merged.back();
        //long long& last_a = temp.first;
        //long long& last_b = temp.second;

        if(r.first <= last_b + 1){
            last_b = std::max(last_b, r.second);
        } else{
            merged.push_back(r);
        }
    }

    long long total_fresh = 0;
    for(auto&[a, b] : merged){
        total_fresh += (b-a +1);
    }
    std::cout << "Fresh IDs: " << total_fresh << std::endl;
}



/*PART 1

void run_day05() {
    std::vector<std::string> input = read_lines("../data/day05.txt");
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> ids;

    bool second_part = false;
    int fresh_count = 0;

    for (const std::string& line : input){
        if(line.empty()){
            second_part = true;
            continue;
        }

        if(!second_part){
            size_t dash = line.find('-');
            long long a = std::stoll(line.substr(0, dash));
            long long b = std::stoll(line.substr(dash + 1));
            if(a > b) std::swap(a, b);
            ranges.push_back({a, b});
        } else {
            ids.push_back(std::stoll(line));
        }
    }
    for (long long id : ids){
        for (auto& [a, b] : ranges){
            if (id >= a && id <= b){
                fresh_count++;
                break;
            }
        }
    }

    for (long long id : ids) {
        for (auto& [a, b] : ranges) {
            if (id >= a && id <= b) {
                fresh_count++;
                break;
            }
        }
    }

    std::cout << "Fresh IDs: " << fresh_count << std::endl;
}


*/