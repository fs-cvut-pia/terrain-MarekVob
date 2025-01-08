#ifndef PATH_P
#define PATH_P

#include "TerrainMap.h"
#include <vector>
#include <string>

// Abstract class for storing path coordinates
class Path {
public:
    Path(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    virtual ~Path() = default;
    virtual bool find() = 0;     // Path finding implementation
    void printStats() const;     // Print statistics
    void saveToFile() const;     // Save path to file
    std::string getName() const; // Path name
protected:
    TerrainMap& map;
    std::vector<Point> path;
    const Point start; 
    const Point finish;
    std::string name;
};

#endif
