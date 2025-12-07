#include "day07.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <unordered_set>
#include <algorithm>

void run_day07() {
    std::vector<std::string> lines = read_lines("../data/day07.txt");

    int rows = lines.size();
    int cols = lines[0].size();

    int s_pos = lines[0].find('S');

    std::vector<bool> beam(cols, false);
    beam[s_pos] = true;

    long long splitCounter = 0;

    for (int row = 1; row < rows; row++) {
        std::vector<bool> next(cols, false);

        for (int c = 0; c < cols; c++) {
            if (!beam[c]) continue;

            if (lines[row][c] == '^') {
                if (c > 0) next[c - 1] = true;
                if (c < cols - 1) next[c + 1] = true;
                splitCounter++;
            } else {
                next[c] = true;
            }
        }
        beam = next;
    }

    std::cout << "Splits: " << splitCounter << "\n";
}
