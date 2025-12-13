#include "day12.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using Grid = std::vector<std::vector<int>>;
using Oris = std::vector<Grid>;
using Shapes = std::vector<Oris>;

struct RegionSpec{
    int W, H;
    std::vector<int> counts;
};


static bool is_shape_header(const std::string& s) {
    // e.g. "12:" or "0:"
    if (s.empty() || s.back() != ':') return false;
    for (size_t i = 0; i + 1 < s.size(); i++)
        if (!std::isdigit((unsigned char)s[i])) return false;
    return true;
}

static bool is_region_line(const std::string& s) {
    // e.g. "12x5: 1 0 1"
    // quick check: must contain 'x' and ':' with digits around
    auto x = s.find('x');
    auto c = s.find(':');
    if (x == std::string::npos || c == std::string::npos || x > c) return false;
    return std::isdigit((unsigned char)s[0]);
}

static Grid parse_shape_grid(const std::vector<std::string>& lines, size_t& i){
    Grid g;
    while(i < lines.size()){
        const std::string& row = lines[i];
        if(row.empty()) break;
        if(is_shape_header(row) || is_region_line(row)) break;
    
        std::vector<int> r;
        r.reserve(row.size());
        for( char ch : row){
            if(ch == '#') r.push_back(1);
            else if(ch == '.') r.push_back(0);
            else throw std::runtime_error("Invalid char in shape row: " + row);
        } 
        g.push_back(std::move(r));
        i++;
    }
    return g;
}


static RegionSpec parse_region(const std::string& line) {
    RegionSpec r;
    auto colon = line.find(':');
    auto x = line.find('x');
    r.W = std::stoi(line.substr(0, x));
    r.H = std::stoi(line.substr(x + 1, colon - (x + 1)));

    std::istringstream iss(line.substr(colon + 1));
    int v;
    while (iss >> v) r.counts.push_back(v);
    return r;
}

Grid rotate90(const Grid& g){
    int h = g.size();
    int w = g[0].size();

    Grid r(w, std::vector<int>(h));
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            r[x][h - 1 - y] = g[y][x];
        }
    }
    return r;
}
Grid trim(const Grid& g) {
    int h = g.size();
    int w = g[0].size();

    int top = h, bottom = -1, left = w, right = -1;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (g[y][x]) {
                top = std::min(top, y);
                bottom = std::max(bottom, y);
                left = std::min(left, x);
                right = std::max(right, x);
            }

    Grid r;
    for (int y = top; y <= bottom; y++) {
        std::vector<int> row;
        for (int x = left; x <= right; x++)
            row.push_back(g[y][x]);
        r.push_back(row);
    }
    return r;
}

bool same_grid(const Grid& a, const Grid& b) {
    if (a.size() != b.size()) return false;
    if (a[0].size() != b[0].size()) return false;

    for (size_t y = 0; y < a.size(); y++)
        for (size_t x = 0; x < a[0].size(); x++)
            if (a[y][x] != b[y][x]) return false;

    return true;
}
Oris generate_orientations(const Grid& base) {
    Oris result;

    Grid cur = trim(base);

    for (int rot = 0; rot < 4; rot++) {
        Grid t = trim(cur);

        bool duplicate = false;
        for (const Grid& existing : result) {
            if (same_grid(existing, t)) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
            result.push_back(t);

        cur = rotate90(cur);
    }

    return result;
}


void run_day12() {
    std::vector<std::string> input = read_lines("../data/day11.txt");

    std::vector<Grid> base_shapes;      // base_shapes[id] = grid
    std::vector<RegionSpec> regions;

    for (size_t i = 0; i < input.size(); ) {
        if (input[i].empty()) { i++; continue; }

        if (is_shape_header(input[i])) {
            int id = std::stoi(input[i].substr(0, input[i].size() - 1));
            i++; // move to first grid row
            Grid g = parse_shape_grid(input, i);

            if ((int)base_shapes.size() <= id) base_shapes.resize(id + 1);
            base_shapes[id] = std::move(g);

            // skip possible blank line
            while (i < input.size() && input[i].empty()) i++;
            continue;
        }

        if (is_region_line(input[i])) {
            regions.push_back(parse_region(input[i]));
            i++;
            continue;
        }

        throw std::runtime_error("Unrecognized line: " + input[i]);
    }
    Shapes shapes;
    shapes.resize(base_shapes.size());
    for(size_t i = 0; i < base_shapes.size(); i++){
        shapes[i] = generate_orientations(base_shapes[i]);
    }

    
}
