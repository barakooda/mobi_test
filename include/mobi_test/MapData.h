#ifndef MAPDATA_H
#define MAPDATA_H

#include <string>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>
#include "json/json.hpp"

struct Point {
    glm::vec3 location;
    glm::vec3 up_vector;
    glm::vec3 forward_vector;
    glm::vec3 right_vector;

    float lane_width;
};

struct Lane {
    int id;
    std::vector<int> predecessor_ids;
    std::vector<int> successor_ids;
    std::vector<Point> points;
};

class MapData {
public:
    bool loadFromFile(const std::filesystem::path& filePath);
    void computeForwardAndRightVectors();
    void print() const;

    const std::vector<Lane>& getLanes() const; // Getter for lanes

private:
    std::vector<Lane> lanes;
};

#endif // MAPDATA_H
