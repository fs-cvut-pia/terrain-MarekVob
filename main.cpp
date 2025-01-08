#include "TerrainMap.h"
#include "Path.h"
#include "Airplane.h"
#include "Boat.h"
#include "Road.h"
#include <vector>
#include <iostream>
#include <string>

Point read_coordinates(int argc, char *argv[], int i_option) {
    Point p;

    if (argc > i_option+1) { p.x = std::atoi(argv[i_option]); p.y = std::atoi(argv[i_option + 1]); }
    else throw std::runtime_error("Coordinates incorrectly specified!");

    return p;
}

int main(int argc, char *argv[]) {
    const int nx = 256;
    const int ny = 256;

    std::string terrain_filename;

    // Load terrain map
    if (argc > 1) terrain_filename = argv[1];
    else { std::cout << "No terrain file specified!" << std::endl; return 0; }

    TerrainMap m(nx,ny,terrain_filename);

    // Load coordinates of start and end points
    Point start = read_coordinates(argc,argv,2);
    Point finish = read_coordinates(argc,argv,4);

   std::vector<Path*> paths = {
    new Airplane(m, "AirplanePath", start, finish),
    new Boat(m, "BoatPath", start, finish),
    new Road(m, "RoadPath", start, finish) 
};

for (auto& p : paths) {
    if (p->find()) {  // Call `find()` and check if path was found
        std::cout << "Path search: " << p->getName() << std::endl;
        std::cout << "=============" << std::endl;
        p->printStats();    // Print statistics
        std::cout << "=============" << std::endl;
        p->saveToFile();    // Save path to file
    } else {
        std::cout << "Failed to find path: " << p->getName() << std::endl;
    }
    delete p; // Free memory
}

}
