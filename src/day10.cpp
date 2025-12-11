#include "day10.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <functional>

// ==========================================================
// =============== Helper Parsing Functions =================
// ==========================================================

// Parse [.##.] into bitmask (for Part 1)
static int parseTargetMask(const std::string& s) {
    int mask = 0;
    for (char c : s) {
        mask <<= 1;
        if (c == '#') mask |= 1;
    }
    return mask;
}

// Parse (0,3,4) into toggle-bitmask (for Part 1)
static int parseButtonMask(const std::string& inside, int N) {
    int mask = 0;
    std::stringstream ss(inside);
    std::string num;

    while (std::getline(ss, num, ',')) {
        if (!num.empty()) {
            int idx = std::stoi(num);
            if (idx >= 0 && idx < N) {
                mask |= (1 << (N - 1 - idx));
            }
        }
    }
    return mask;
}

// Parse {3,5,4,7} into vector<int> (Part 2 target)
static std::vector<int> parseTargetCounters(const std::string& inside) {
    std::vector<int> result;
    std::stringstream ss(inside);
    std::string num;

    while (std::getline(ss, num, ',')) {
        if (!num.empty()) result.push_back(std::stoi(num));
    }
    return result;
}

// Parse (1,3) into add-vector for counters (Part 2)
static std::vector<int> parseButtonAddVector(const std::string& inside, int K) {
    std::vector<int> add(K, 0);
    std::stringstream ss(inside);
    std::string num;

    while (std::getline(ss, num, ',')) {
        if (!num.empty()) {
            int idx = std::stoi(num);
            if (idx >= 0 && idx < K) {
                add[idx] = 1;
            }
        }
    }
    return add;
}

// ==========================================================
// =============== BFS for Part 1 (bitmask) =================
// ==========================================================

static int solveMachinePart1(int targetMask, const std::vector<int>& buttons, int N) {
    const int MAXS = 1 << N;
    std::vector<bool> visited(MAXS, false);

    std::queue<std::pair<int,int>> q;
    q.push({0, 0});      // start at all-off mask
    visited[0] = true;

    while (!q.empty()) {
        auto [state, dist] = q.front();
        q.pop();

        if (state == targetMask)
            return dist;

        for (int mask : buttons) {
            int next = state ^ mask;
            if (!visited[next]) {
                visited[next] = true;
                q.push({next, dist + 1});
            }
        }
    }

    return -1;
}
long long encodeVector(const std::vector<int>& vec, const std::vector<int>& basePow) {
    long long key = 0;
    for (int i = 0; i < (int)vec.size(); i++)
        key += 1LL * vec[i] * basePow[i];
    return key;
}

int solveMachinePart2_mitm(const std::vector<int>& target,
                           const std::vector<std::vector<int>>& buttons)
{
    int K = target.size();
    int M = buttons.size();
    if (M == 0) return 999999999;

    // Precompute base powers for encoding vectors
    std::vector<int> base(K);
    for (int k = 0; k < K; k++) base[k] = target[k] + 1;

    std::vector<int> basePow(K);
    basePow[0] = 1;
    for (int k = 1; k < K; k++) basePow[k] = basePow[k-1] * base[k];

    int L = M / 2;

    std::vector<std::vector<int>> left(buttons.begin(), buttons.begin() + L);
    std::vector<std::vector<int>> right(buttons.begin() + L, buttons.end());

    std::unordered_map<long long, int> leftMap;

    // DFS on left side
    std::function<void(int, std::vector<int>&, int)> dfsLeft =
    [&](int idx, std::vector<int>& state, int cost) {
        if (idx == (int)left.size()) {
            long long key = encodeVector(state, basePow);
            auto it = leftMap.find(key);
            if (it == leftMap.end() || cost < it->second)
                leftMap[key] = cost;
            return;
        }

        // compute max presses for this button
        int maxP = 1000000000;
        for (int k = 0; k < K; k++)
            if (left[idx][k] == 1)
                maxP = std::min(maxP, target[k] - state[k]);
        if (maxP < 0) maxP = 0;

        for (int p = 0; p <= maxP; p++) {
            for (int k = 0; k < K; k++)
                state[k] += p * left[idx][k];

            dfsLeft(idx + 1, state, cost + p);

            for (int k = 0; k < K; k++)
                state[k] -= p * left[idx][k];
        }
    };

    // DFS on right side, match against leftMap
    int best = 1e9;
    std::function<void(int, std::vector<int>&, int)> dfsRight =
    [&](int idx, std::vector<int>& state, int cost) {
        if (cost >= best) return;

        if (idx == (int)right.size()) {
            std::vector<int> need(K);
            for (int k = 0; k < K; k++) {
                need[k] = target[k] - state[k];
                if (need[k] < 0 || need[k] > target[k]) return;
            }

            long long key = encodeVector(need, basePow);
            auto it = leftMap.find(key);
            if (it != leftMap.end()) {
                best = std::min(best, cost + it->second);
            }
            return;
        }

        int maxP = 1000000000;
        for (int k = 0; k < K; k++)
            if (right[idx][k] == 1)
                maxP = std::min(maxP, target[k] - state[k]);
        if (maxP < 0) maxP = 0;

        for (int p = 0; p <= maxP; p++) {
            for (int k = 0; k < K; k++)
                state[k] += p * right[idx][k];

            dfsRight(idx + 1, state, cost + p);

            for (int k = 0; k < K; k++)
                state[k] -= p * right[idx][k];
        }
    };

    std::vector<int> start(K, 0);
    dfsLeft(0, start, 0);

    std::fill(start.begin(), start.end(), 0);
    dfsRight(0, start, 0);

    return best;
}

// ==========================================================
// ===================== Main Run ===========================
// ==========================================================

void run_day10() {
    std::vector<std::string> input = read_lines("../data/day10.txt");

    long long totalPart1 = 0;
    long long totalPart2 = 0;

    for (std::string line : input) {
        if (line.empty()) continue;

        // ----------- Extract root [ ... ] -----------
        size_t lb = line.find('[');
        size_t rb = line.find(']');
        std::string rootStr = line.substr(lb + 1, rb - lb - 1);
        int N = rootStr.size();

        int targetMaskPart1 = parseTargetMask(rootStr);

        // ----------- Extract target counters { ... } (Part 2) -----------
        size_t cb = line.find('{');
        size_t ce = line.find('}', cb);
        std::string curly = line.substr(cb + 1, ce - cb - 1);
        std::vector<int> targetCounters = parseTargetCounters(curly);

        // ----------- Parse all buttons ( ... ) -----------
        std::vector<int> buttonsPart1;
        std::vector<std::vector<int>> buttonsPart2;

        size_t pos = rb + 1;
        while (true) {
            size_t lp = line.find('(', pos);
            if (lp == std::string::npos) break;

            size_t rp = line.find(')', lp);
            if (rp == std::string::npos) break;

            std::string inside = line.substr(lp + 1, rp - lp - 1);

            // Skip { } block at end (sometimes parsed like "( {something}")
            if (!inside.empty() && inside[0] == '{') {
                pos = rp + 1;
                continue;
            }

            // Parse as toggle mask for Part 1
            int mask = parseButtonMask(inside, N);
            buttonsPart1.push_back(mask);

            // Parse as add-vector for Part 2
            buttonsPart2.push_back(parseButtonAddVector(inside,
                                                        targetCounters.size()));

            pos = rp + 1;
        }

        // ----------- Solve Part 1 -----------
        int presses1 = solveMachinePart1(targetMaskPart1, buttonsPart1, N);
        totalPart1 += presses1;

        // ----------- Solve Part 2 -----------
        int presses2 = solveMachinePart2_mitm(targetCounters, buttonsPart2);

        totalPart2 += presses2;
    }

    std::cout << "Day 10 - Part 1: " << totalPart1 << "\n";
    std::cout << "Day 10 - Part 2: " << totalPart2 << "\n";
}
