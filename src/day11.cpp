#include "day11.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>


std::unordered_map<std::string, std::vector<std::string>> build_graph(const std::vector<std::string>& lines){
    std::unordered_map<std::string, std::vector<std::string>> graph;
    for(const std::string& line : lines){

        size_t pos = line.find(':');
        std::string node = line.substr(0, pos);
        std::string rest = line.substr(pos+1);

            //trim leading spaces
        while(!rest.empty() && rest[0] == ' '){
            rest.erase(rest.begin());
        }

        std::vector<std::string> neighbors;
        std::istringstream iss(rest);
        std::string neigh;

        while(iss >> neigh){
            neighbors.push_back(neigh);
        }
        graph[node] = neighbors;
    }

    return graph;
}



// assuming there is a topological order // DAG
long long count_paths(const std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& node, const std::string& target, std::unordered_map<std::string, long long>& memo){
    if(node == target) return 1; //BAse case, reached target
    if(memo.count(node)) return memo[node];

    long long total = 0;
    auto it = graph.find(node);
    if(it != graph.end()){
        for(const std::string& neigh : it->second){
            total += count_paths(graph, neigh, target, memo);
        }
    }
    //node has no outgoing edges and not reached "out" -> 0 paths
    memo[node] = total;
    return total;
}

long long count_paths2(
    const std::unordered_map<std::string, std::vector<std::string>>& graph,
    const std::string& node,
    const std::string& target,
    bool seen_dac,
    bool seen_fft,
    std::unordered_map<std::string, long long>& memo)
{
    if (node == target)
        return (seen_dac && seen_fft) ? 1 : 0;

    std::string key = node + "|" + (seen_dac?"1":"0") + "|" + (seen_fft?"1":"0");
    if (memo.count(key))
        return memo[key];

    long long total = 0;

    auto it = graph.find(node);
    if (it != graph.end()) {
        for (const auto& neigh : it->second) {
            bool next_dac = seen_dac || (neigh == "dac");
            bool next_fft = seen_fft || (neigh == "fft");
            total += count_paths2(graph, neigh, target, next_dac, next_fft, memo);
        }
    }

    memo[key] = total;
    return total;
}


void run_day11(){

    std::vector<std::string> input = read_lines("../data/day11.txt");
    auto graph = build_graph(input);
    // example: print neighbors of "jcy"
    for (auto& n : graph["jcy"]) {
        std::cout << n << " ";
    }
    
    //assuming its acyclic, do dp.
    std::string start = "svr";
    std::string end   = "out";

    std::unordered_map<std::string, long long> memo;

    long long paths = count_paths(graph, start, end, memo);

    std::cout << "Number of paths: " << paths << "\n";
    //part 2

    std::unordered_map<std::string, long long> memo2;


    long long result = count_paths2(graph, "svr", "out", false, false, memo2);

    std::cout << result << "\n";


}