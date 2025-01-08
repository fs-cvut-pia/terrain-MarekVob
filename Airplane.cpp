#include "Airplane.h"

Airplane::Airplane(TerrainMap& terrain, std::string routeName, Point startPoint, Point endPoint)
    : Path(terrain, routeName, startPoint, endPoint) {}

bool Airplane::find() {
    // Bresenham line drawing algorithm
    int xStart = start.x, yStart = start.y;
    int xEnd = finish.x, yEnd = finish.y;

    int deltaX = abs(xEnd - xStart), deltaY = abs(yEnd - yStart);
    int stepX = (xStart < xEnd) ? 1 : -1;
    int stepY = (yStart < yEnd) ? 1 : -1;
    int error = deltaX - deltaY;

    path.clear();  // Reset existing path
    path.push_back(Point(xStart, yStart));

    while (xStart != xEnd || yStart != yEnd) {
        int doubleError = error * 2;
        if (doubleError > -deltaY) {
            error -= deltaY;
            xStart += stepX;
        }
        if (doubleError < deltaX) {
            error += deltaX;
            yStart += stepY;
        }
        path.push_back(Point(xStart, yStart));
    }

    return true;  // Path successfully created
}
