#include "day03.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>


//PART 2
void run_day03(){

    std::vector<std::string> input = read_lines("../data/day03.txt");

    
    long long sum = 0;
    for(int i = 0; i < input.size(); i++){
        int arr[12]; 
        for (int d = 0; d < 12; ++d) {
            arr[d] = input[i][d] - '0';
        }

        for (int j = 12; j < input[i].size(); j++){
            int nextDigit = input[i][j] - '0';

            for(int k = 0; k < 12; k++){
                
                if((k < 11) && arr[k] < arr[k+1]){
                    for(int l = k; l < 11; l++){
                        arr[l] = arr[l + 1]; 
                    }
                    arr[11] = nextDigit;
                    break; //stop comparing, next digit has been consumed
                } else if (k == 11 && arr[k] < nextDigit)
                {
                    arr[k] = nextDigit;
                }
                

            }

            
        }
        long long value = 0;
        for(int k = 0; k < 12; k++){
            value = value * 10 + arr[k];
        }
        
        sum += value;
    }

    std::cout << "The sum of all highest 12 digit numbers is: " << sum << ".";


}


/* PART 1


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

*/