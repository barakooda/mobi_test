#include "Path.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

void Path::addPoint(const glm::vec3& point) {
    points.push_back(point);
}

void Path::removeLastPoint() {
    if (!points.empty()) {
        points.pop_back();
    }
}

const std::vector<glm::vec3>& Path::getPoints() const {
    return points;
}

float Path::calculateLength() const {
    float totalLength = 0.0f;

    for (size_t i = 1; i < points.size(); ++i) {
        totalLength += glm::distance(points[i - 1], points[i]);
    }

    return totalLength;
}
