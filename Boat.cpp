#include "Boat.h"
#include <queue>
#include <limits>
#include <map>
#include <algorithm>

Boat::Boat(TerrainMap& m, std::string name, Point start, Point finish)
    : Path(m, name, start, finish) {}

bool Boat::find() {
    // Dijkstra's algorithm
    std::priority_queue<
        std::pair<double, Point>,
        std::vector<std::pair<double, Point>>,
        std::greater<std::pair<double, Point>>
    > pq;

    std::map<Point, double> distances;
    std::map<Point, Point> previous;

    // Init distances to infinity
    for (int x = 0; x < map.nx; ++x) {
        for (int y = 0; y < map.ny; ++y) {
            distances[{x, y}] = std::numeric_limits<double>::infinity();
        }
    }
    // Starting point distance to 0
    distances[start] = 0.0;
    pq.push({0.0, start});

    // Directions (8 directions for diagonal movement)
    const std::vector<Point> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    while (!pq.empty()) {
        auto current_pair = pq.top();
        pq.pop();

        double current_dist = current_pair.first;
        Point current = current_pair.second;

        // If reached the finish, break
        if (current == finish) break;

        for (const auto& dir : directions) {
            Point neighbor = current + dir;
            if (!map.validCoords(neighbor)) continue;

            // Check elevation constraint: boat can only travel on water (height < 0)
            int neighbor_alt = map.alt(neighbor);
            if (neighbor_alt >= 0 && neighbor != start && neighbor != finish) continue;

            double new_dist = current_dist + dir.length();

            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                previous[neighbor] = current;
                pq.push({new_dist, neighbor});
            }
        }
    }

    // Reconstruct path
    if (distances[finish] == std::numeric_limits<double>::infinity()) return false;

    Point step = finish;
    while (step != start) {
        path.push_back(step);
        step = previous[step];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return true;
}
