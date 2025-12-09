#include "day09.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>


/*
void run_day09() {

    std::vector<std::string> input = read_lines("../data/day09.txt");

    // Read coordinates
    std::vector<Coord2D> coords;
    coords.reserve(input.size());

    for (const std::string &line : input) {
        std::stringstream ss(line);
        int a, b;
        char comma;
        ss >> a >> comma >> b;
        coords.push_back({a, b});
    }

    // PART 1: compute all areas and store (area,i,j)
    std::vector<AreaInfo> areas;

    for (int i = 0; i < coords.size(); i++) {
        for (int j = i + 1; j < coords.size(); j++) {
            long long a = getSurface(coords[i], coords[j]);
            areas.push_back({a, i, j});
        }
    }

    // Sort by area ascending
    std::sort(areas.begin(), areas.end(),
              [](const AreaInfo &A, const AreaInfo &B) {
                  return A.area < B.area;
              });

    std::cout << "Largest area = " << areas.back().area << std::endl;


}
*/

// We already have this in util.h:
/// struct Coord2D { int x, y; };
/// long long getSurface(const Coord2D&, const Coord2D&);

#include "day09.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// A rectangle formed by two red tiles
struct Rectangle {
    int minX, minY, maxX, maxY;
    long long area;
};

// Build a rectangle from two Coord2D tiles
static Rectangle makeRect(const Coord2D& a, const Coord2D& b) {
    int minX = std::min(a.x, b.x);
    int minY = std::min(a.y, b.y);
    int maxX = std::max(a.x, b.x);
    int maxY = std::max(a.y, b.y);

    long long area = (long long)(maxX - minX + 1) * (long long)(maxY - minY + 1);

    return Rectangle{minX, minY, maxX, maxY, area};
}

// Check whether ANY polygon edge intersects the INTERIOR of the rectangle
static bool traversed(const Rectangle& r, const std::vector<Coord2D>& seats) {
    // Shrink interior by 1 on each side: we test ONLY inside space
    int innerMinX = r.minX + 1;
    int innerMinY = r.minY + 1;
    int innerMaxX = r.maxX - 1;
    int innerMaxY = r.maxY - 1;

    // If the rectangle is too thin (width or height < 3), it has no interior
    if (innerMinX > innerMaxX || innerMinY > innerMaxY)
        return false;

    int n = seats.size();

    for (int i = 0; i < n; i++) {
        // polygon segment between seats[i] and seats[(i+1)%n]
        Coord2D p1 = seats[i];
        Coord2D p2 = seats[(i + 1) % n];

        int segMinX = std::min(p1.x, p2.x);
        int segMaxX = std::max(p1.x, p2.x);
        int segMinY = std::min(p1.y, p2.y);
        int segMaxY = std::max(p1.y, p2.y);

        // AABB intersection check with rectangle interior
        bool noOverlap =
            (segMaxX < innerMinX) || (segMinX > innerMaxX) ||
            (segMaxY < innerMinY) || (segMinY > innerMaxY);

        if (!noOverlap) {
            // Segment intersects the interior → rectangle invalid
            return true;
        }
    }

    return false;
}

void run_day09() {

    // -------------------------
    // Read input
    // -------------------------
    std::vector<std::string> input = read_lines("../data/day09.txt");
    std::vector<Coord2D> seats;
    seats.reserve(input.size());

    for (auto &line : input) {
        std::stringstream ss(line);
        int x, y;
        char comma;
        ss >> x >> comma >> y;
        seats.push_back({x, y});
    }

    int n = seats.size();

    // -------------------------
    // Build all candidate rectangles (Part 1 + Part 2)
    // -------------------------
    std::vector<Rectangle> rects;
    rects.reserve((long long)n * (n - 1) / 2);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            rects.push_back(makeRect(seats[i], seats[j]));
        }
    }

    // -------------------------
    // PART 1: largest area
    // -------------------------
    long long part1 = 0;
    for (auto &r : rects)
        part1 = std::max(part1, r.area);

    std::cout << "Part 1: " << part1 << "\n";

    // -------------------------
    // PART 2: largest *valid* interior rectangle
    // -------------------------
    long long part2 = 0;

    for (auto &r : rects) {
        if (!traversed(r, seats)) {
            part2 = std::max(part2, r.area);
        }
    }

    std::cout << "Part 2: " << part2 << "\n";
}
