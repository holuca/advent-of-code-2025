#include "day03.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>

void run_day03(){

    std::vector<std::string> input = read_lines("../data/day03.txt");

    
    int sum = 0;
    for(int i = 0; i < input.size(); i++){
        int firstDigit = input[i][0] - '0';
        int secondDigit = input[i][1] - '0';
        int arr[2] = {firstDigit, secondDigit };
        for (int j = 2; j < input[0].size(); j++){

            int nextDigit = input[i][j] - '0';
            if(arr[0] < arr[1]){
                arr[0] = arr[1];
                arr[1] = nextDigit;
            } else if (arr[1] < nextDigit)
            {
                arr[1] = nextDigit;
            }
            
        }
        sum += (arr[0] * 10 + arr[1]);
    }

    std::cout << "The sum of all highest double digit numbers is: " << sum << ".";


}