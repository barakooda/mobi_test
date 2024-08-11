#pragma once

#include <vector>
#include <glm/glm.hpp>

class Path {
public:
    void addPoint(const glm::vec3& point);
    void removeLastPoint();
    const std::vector<glm::vec3>& getPoints() const;
    float calculateLength() const;

private:
    std::vector<glm::vec3> points;
};
