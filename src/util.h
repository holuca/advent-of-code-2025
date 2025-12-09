#pragma once

#include <string>
#include <vector>
#include <math.h>
std::vector<std::string> read_lines(const std::string& path);



struct Range{
    long long a;
    long long b;
};

long long applyOp(long long a, char op, long long b);

struct Point3D{
    double x;
    double y;
    double z;
    /* members are constructed twice
    Point3D(double x_, double y_, double z_){
        x = x_;
        y = y_;
        z = z_;
    }
    */
    Point3D(double x_, double y_, double z_) 
        : x(x_), y(y_), z(z_){} //member initializer list, inits each variable before the constructor body runs
};

double getDistance3D(const Point3D& a, const Point3D& b);


struct Coord2D{
    int x;
    int y;
};

long long getSurface(const Coord2D& c1, const Coord2D& c2);

struct Edge{
    double dist;
    int a;
    int b;
};

struct UnionFind{
    std::vector<int> parent;
    std::vector<int> size;

    UnionFind(int n){
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x){
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
/*
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return;

        //union by size
        if(size[a] < size[b]) std::swap(a, b);

        parent[b] = a;
        size[a] += size[b];
    }


*/
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if(a==b) return false; // merge;

        if(size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }




    int component_size(int x){
        return size[find(x)];
    }


};