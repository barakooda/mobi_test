#ifndef MAPDATA_H
#define MAPDATA_H

#include <string>
#include <vector>
#include <filesystem>
#include "json/json.hpp"

struct Point {
    float x, y, z;
    float up_x, up_y, up_z;
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
    void print() const;

private:
    std::vector<Lane> lanes;
};

#endif // MAPDATA_H
