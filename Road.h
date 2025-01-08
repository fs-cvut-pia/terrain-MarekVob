#ifndef ROAD_H
#define ROAD_H

#include "TerrainMap.h"  
#include "Path.h" 

class Road : public Path {
public:
    Road(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);

    // Method to find the path for the road
    bool find();
};

#endif
