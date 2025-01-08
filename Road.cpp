#include "Road.h"
#include <deque>
#include <cmath>
#include <vector>
#include <iostream>

Road::Road(TerrainMap& terrain, std::string routeLabel, Point origin, Point destination) 
    : Path(terrain, routeLabel, origin, destination) {}

float calculateDistance(int dx, int dy) {
    // Calculate Euclidean distance
    return std::sqrt(dx * dx + dy * dy);
}

bool Road::find() {
    Matrix<float> costMap(256, 256);
    costMap.zero();  // Initialize cost map
    Matrix<Point> previousMap(256, 256);
    std::deque<Point> pendingPoints;
    pendingPoints.push_front(start);

    while (!pendingPoints.empty()) {
        Point current = pendingPoints.back();
        pendingPoints.pop_back();

        // Check adjacent points
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                Point adjacent(current.x + dx, current.y + dy);
                if (!map.validCoords(adjacent)) continue;

                float newCost = costMap(current.x, current.y) + calculateDistance(dx, dy);

                // Update cost if path is better and elevation is acceptable
                if ((costMap(adjacent.x, adjacent.y) == 0 || newCost < costMap(adjacent.x, adjacent.y)) &&
                    ((map.alt(adjacent.x, adjacent.y) > 0 && 
                      std::abs(map.alt(current) - map.alt(adjacent)) < 60) || 
                      adjacent == finish)) {

                    costMap(adjacent.x, adjacent.y) = newCost;
                    previousMap(adjacent.x, adjacent.y) = current;
                    pendingPoints.push_front(adjacent);
                }
            }
        }
    }

    path.clear();
    if (costMap(finish.x, finish.y) == 0) {
        std::cout << "Path not found!\n";  // Path not found
        return false;
    }

    // Reconstruct path from finish to start
    for (Point current = finish; current != start; current = previousMap(current)) {
        path.insert(path.begin(), current);
    }
    path.insert(path.begin(), start);

    return true;
}
