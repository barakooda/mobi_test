#include "mobi_test/MapData.h"
#include <fstream>
#include <iostream>

// for convenience
using json = nlohmann::json;

bool MapData::loadFromFile(const std::filesystem::path& filePath) {
    // Open the file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return false;
    }

    // Parse the JSON
    json jsonData;
    file >> jsonData;

    // Clear current lanes
    lanes.clear();

    // Read lanes from JSON
    for (const auto& laneJson : jsonData["lanes"]) {
        Lane lane;
        lane.id = laneJson["id"];
        lane.predecessor_ids = laneJson["predecessor_ids"].get<std::vector<int>>();
        lane.successor_ids = laneJson["successor_ids"].get<std::vector<int>>();

        for (const auto& pointJson : laneJson["points"]) {
            Point point;
            point.x = pointJson["location"]["x"];
            point.y = pointJson["location"]["y"];
            point.z = pointJson["location"]["z"];
            point.up_x = pointJson["up_vector"]["x"];
            point.up_y = pointJson["up_vector"]["y"];
            point.up_z = pointJson["up_vector"]["z"];
            point.lane_width = pointJson["lane_width"];
            lane.points.push_back(point);
        }

        lanes.push_back(lane);
    }

    return true;
}

void MapData::print() const {
    for (const auto& lane : lanes) {
        std::cout << "Lane ID: " << lane.id << std::endl;
        std::cout << "Predecessor IDs: ";
        for (const auto& pred_id : lane.predecessor_ids) {
            std::cout << pred_id << " ";
        }
        std::cout << std::endl;

        std::cout << "Successor IDs: ";
        for (const auto& succ_id : lane.successor_ids) {
            std::cout << succ_id << " ";
        }
        std::cout << std::endl;

        for (const auto& point : lane.points) {
            std::cout << "Point: (" << point.x << ", " << point.y << ", " << point.z << "), ";
            std::cout << "Up Vector: (" << point.up_x << ", " << point.up_y << ", " << point.up_z << "), ";
            std::cout << "Lane Width: " << point.lane_width << std::endl;
        }
        std::cout << std::endl;
    }
}
