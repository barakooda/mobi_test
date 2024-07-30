#include "mobi_test/SaveMapData.h"
#include <fstream>
#include "json/json.hpp"
#include <iostream>

using json = nlohmann::json;

// Function to convert a Point to JSON
nlohmann::json pointToJson(const Point& point) {
    return nlohmann::json{
        {"location", {point.location.x, point.location.y, point.location.z}},
        {"up_vector", {point.up_vector.x, point.up_vector.y, point.up_vector.z}},
        {"forward_vector", {point.forward_vector.x, point.forward_vector.y, point.forward_vector.z}},
        {"right_vector", {point.right_vector.x, point.right_vector.y, point.right_vector.z}},
        {"lane_width", point.lane_width}
    };
}

// Function to convert a Lane to JSON
nlohmann::json laneToJson(const Lane& lane) {
    nlohmann::json pointsJson;
    for (const auto& point : lane.points) {
        pointsJson.push_back(pointToJson(point));
    }

    return nlohmann::json{
        {"id", lane.id},
        {"predecessor_ids", lane.predecessor_ids},
        {"successor_ids", lane.successor_ids},
        {"points", pointsJson},
        {"length", lane.length}
    };
}

bool saveMapDataToFile(const MapData& mapData, const std::filesystem::path& filePath) {
    nlohmann::json jsonData;

    for (const auto& lane : mapData.getLanes()) {
        jsonData["lanes"].push_back(laneToJson(lane));
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    file << jsonData.dump(4); // Pretty print with 4-space indentation
    file.close();

    return true;
}