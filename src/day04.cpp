#include "day02.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>

//PART 2
void run_day04(){
    std::vector<std::string> input = read_lines("../data/day04.txt");
    int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    bool stillRemovable = true;
    int totalCount = 0;
    int numberOfIteration = 0;

    while(stillRemovable){
        int count = 0;
        stillRemovable = false;
        for (int i = 0; i < input.size(); i++){
            for(int j = 0; j < input[i].size(); j++){
                if(input[i][j] != '@') continue;

                int neighbor = 0;
                for(int n = 0; n < 8; n++){
                    int n_row = i + dir_row[n];
                    int n_col = j + dir_col[n];

                    if(n_row >= 0 && n_row < input.size() && n_col >= 0 && n_col < input[i].size() && input[n_row][n_col] == '@'){
                        neighbor++;
                    }
                }
                if(neighbor < 4){
                    count++;
                    input[i][j] = '.';
                    stillRemovable = true; //as soon as there is one paperroll which has been accessed, again true
                }
            }
        }    
        numberOfIteration ++;
        totalCount += count;

    }
    std::cout << "The total number of accesible rolls after convergence is " << totalCount << " after " << numberOfIteration << " iterations.";

}
/* PART 1

void run_day04(){
    std::vector<std::string> input = read_lines("../data/day04.txt");
    int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;
    for (int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            if(input[i][j] != '@') continue;

            int neighbor = 0;
            for(int n = 0; n < 8; n++){
                int n_row = i + dir_row[n];
                int n_col = j + dir_col[n];

                if(n_row >= 0 && n_row < input.size() && n_col >= 0 && n_col < input[i].size() && input[n_row][n_col] == '@'){
                    neighbor++;
                }
            }
            if(neighbor < 4){
                count++;
                std::cout << "Accessible roll at (" << i << ", " << j << ")\n";
            }
        }
    }    
    std::cout << "The total number of accesible rolls is: " << count << ".";
}


*/