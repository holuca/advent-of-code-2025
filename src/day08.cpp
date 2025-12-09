#include "day08.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

//PART 2
void run_day08(){

    std::vector<std::string> input = read_lines("../data/day08.txt");
    int n = input.size();
    std::vector<Point3D> junctions;
    junctions.reserve(n);

    UnionFind unionFind(n); 

    for(std::string line : input){
        std::stringstream ss(line);
        double x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;

        junctions.emplace_back(Point3D(x, y, z));
    }

    //get all edges
    std::vector<Edge> edges;
    edges.reserve((long long)n*(n-1) /2);


    for(int i = 0; i < n; i++){
        for(int j =i+1; j < n; j++){
            double d = getDistance3D(junctions[i], junctions[j]);
            edges.push_back({d, i, j});
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge &e2){return e1.dist < e2.dist;});

/*
    int root = unionFind.find(0);
    int edgeCounter = 0;

    while(unionFind.size[root] < 1000){
        unionFind.join(edges[edgeCounter].a, edges[edgeCounter].b);
        edgeCounter++;
        root = unionFind.find(0);
    }

    Point3D secondToLast = junctions[edges[edgeCounter -1].a];
    Point3D last = junctions[edges[edgeCounter-1].b];

    long long answer =  secondToLast.x * last.x;

*/
    int components = n;
    int edgeCounter = 0;

    while (components > 1) {
        int a = edges[edgeCounter].a;
        int b = edges[edgeCounter].b;

        if (unionFind.join(a, b)) {
            components--;      // merged successfully
        }

        edgeCounter++;
    }
    Point3D p1 = junctions[edges[edgeCounter - 1].a];
    Point3D p2 = junctions[edges[edgeCounter - 1].b];

    long long answer = (long long)p1.x * (long long)p2.x;


    std::cout << "Answer: " << answer << std::endl;
}


/*PART 1

void run_day08(){

    std::vector<std::string> input = read_lines("../data/day08.txt");
    int n = input.size();
    std::vector<Point3D> junctions;
    junctions.reserve(n);

    UnionFind unionFind(n); 

    for(std::string line : input){
        std::stringstream ss(line);
        double x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;

        junctions.emplace_back(Point3D(x, y, z));
    }

    //get all edges
    std::vector<Edge> edges;
    edges.reserve((long long)n*(n-1) /2);


    for(int i = 0; i < n; i++){
        for(int j =i+1; j < n; j++){
            double d = getDistance3D(junctions[i], junctions[j]);
            edges.push_back({d, i, j});
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge &e2){return e1.dist < e2.dist;});


    int K = 1000;
    for(int i = 0; i < K; i++){
        unionFind.join(edges[i].a, edges[i].b);
    }1LL
    std::unordered_map<int, int> compSize;
    for(int i = 0; i < n; i++){
        int root = unionFind.find(i);
        compSize[root] = unionFind.size[root];
    }
    std::vector<int > sizes;
    for(auto &p : compSize)
        sizes.push_back(p.second);
    //sort descending
    std::sort(sizes.rbegin(), sizes.rend());


    long long answer = 1LL * sizes[0] * sizes[1] * sizes[2];
    std::cout << "Answer: " << answer << std::endl;
}

*/