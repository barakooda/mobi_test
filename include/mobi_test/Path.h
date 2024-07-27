#ifndef PATH_H
#define PATH_H

#include <vector>
#include <glm/glm.hpp>
#include "MapData.h"

struct Path {
    std::vector<Point> points;
    float length = 0.0f;
};

#endif // PATH_H
