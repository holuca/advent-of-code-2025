#include "day06.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <cctype>


/* PART 1

void run_day06(){
    std::vector<std::string> lines = read_lines("../data/day06.txt");
    std::vector<std::vector<int>> num_lines;
    std::vector<char> symbols;

    for(const std::string& line : lines){

        if (line.empty()) continue;

        size_t pos = line.find_first_not_of(' ');
        if (pos == std::string::npos) continue;   // skip blank

        char first = line[pos];

        if (std::isdigit(first)) {
            std::stringstream ss(line);
            std::vector<int> nums;
            int value;

            while (ss >> value)
                nums.push_back(value);

            num_lines.push_back(nums);
        }
        else {
            for(char c : line)
                if (c == '*' || c == '+')
                    symbols.push_back(c);
        }
    }

    long long total = 0;
    int cols = num_lines[0].size();
    int rows = num_lines.size();

    for(int col = 0; col < cols; col++){
        long long val = num_lines[0][col];
        char op = symbols[col];

        for(int row = 1; row < rows; row++){
            val = applyOp(val, op, num_lines[row][col]);
        }

        total += val;
    }

    std::cout << "The total number is: " << total << "." << std::endl;
}


*/

//PART 2


bool isSeparatorColumn(int c, const std::string &symbols, int rows, const std::vector<std::string> &num_lines) {
    if (symbols[c] != ' ') return false;
    for (int r = 0; r < rows; r++) {
        if (num_lines[r][c] != ' ') return false;
    }
    return true;
}



void run_day06() {
    std::vector<std::string> lines = read_lines("../data/day06.txt");

    // Pad to rectangle -> otherwise anoying to debug
    size_t maxw = 0;
    for (auto &s : lines) maxw = std::max(maxw, s.size());
    for (auto &s : lines) s.resize(maxw, ' ');

    std::vector<std::string> num_lines(lines.begin(), lines.end() - 1);
    std::string symbols = lines.back();

    int rows = num_lines.size();
    int cols = symbols.size();
    long long total = 0;

    int c = cols - 1;

    while (c >= 0) {

        while (c >= 0 && isSeparatorColumn(c, symbols, rows, num_lines))
            c--;

        if (c < 0) break;


        int block_end = c;
        int block_start = c;
        while (block_start >= 0 && !isSeparatorColumn(block_start, symbols, rows, num_lines))
            block_start--;
        block_start++;  // Adjust to first non-separator

        // Find operator column inside block
        int op_col = -1;
        for (int col = block_start; col <= block_end; col++) {
            if (symbols[col] == '*' || symbols[col] == '+') {
                op_col = col;
                break;
            }
        }

        if (op_col == -1) {
            throw std::runtime_error("No operator found inside block!");
        }

        char op = symbols[op_col];

        // Collect vertical numbers (columns from block_start -> block_end)
        std::vector<long long> numbers;
        for (int col = block_start; col <= block_end; col++) {

            std::string digits = "";
            for (int r = 0; r < rows; r++) {
                char ch = num_lines[r][col];
                if (std::isdigit(ch))
                    digits.push_back(ch);
            }

            if (!digits.empty())
                numbers.push_back(std::stoll(digits));
        }

        long long value = numbers[0];
        for (int i = 1; i < numbers.size(); i++)
            value = applyOp(value, op, numbers[i]);

        total += value;

        c = block_start - 1;
    }

    std::cout << "Grand total using cephalopod math: " << total << "\n";
}
