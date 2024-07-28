
#ifndef POINT_H
#define POINT_H

#include <glm/glm.hpp>

struct Point {
    glm::vec3 location;
    glm::vec3 up_vector;
    glm::vec3 forward_vector;
    glm::vec3 right_vector;
    float lane_width;
};

#endif // POINT_H
