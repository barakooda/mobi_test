#include "mobi_test/MapData.h"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

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
        //if (lane.id > 20) {
        //    return true;
        //}
        
        lane.predecessor_ids = laneJson["predecessor_ids"].get<std::vector<int>>();
        lane.successor_ids = laneJson["successor_ids"].get<std::vector<int>>();

        for (const auto& pointJson : laneJson["points"]) {
            Point point;
            point.location = glm::vec3(
                pointJson["location"]["x"],
                pointJson["location"]["y"],
                pointJson["location"]["z"]
            );
            point.up_vector = glm::vec3(
                pointJson["up_vector"]["x"],
                pointJson["up_vector"]["y"],
                pointJson["up_vector"]["z"]
            );
            point.lane_width = pointJson["lane_width"];
            lane.points.push_back(point);
        }

        ComputeLaneLength(const_cast<Lane&>(lane));
        ComputeForwardAndRightVector(const_cast<Lane&>(lane));

        lanes.push_back(lane);
    }

    // Compute vectors after loading data
    

    return true;
}

void MapData::ComputeForwardAndRightVector(Lane& lane) {
    
        for (size_t i = 0; i < lane.points.size(); ++i) {
            Point& point = lane.points[i];

            if (i < lane.points.size() - 1) {
                Point& next_point = lane.points[i + 1];
                point.forward_vector = glm::normalize(next_point.location - point.location);
            } else {
                // For the last point, use the forward vector of the previous point
                if (i > 0) {
                    Point& prev_point = lane.points[i - 1];
                    point.forward_vector = prev_point.forward_vector;
                } else {
                    point.forward_vector = glm::vec3(0.0f, 0.0f, 0.0f); // Default if only one point exists
                }
            }

            // Compute right vector as cross product of forward and up vectors
            point.right_vector = glm::normalize(glm::cross(point.forward_vector, point.up_vector));
        }
    
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
        
        std::cout << "Length: ";
        std::cout << lane.length;
        std::cout << std::endl;

        bool is_debug_points = false;
        if (is_debug_points) {

            for (const auto& point : lane.points) 
            
            {
                std::cout << "Point: (" << point.location.x << ", " << point.location.y << ", " << point.location.z << "), ";
                std::cout << "Up Vector: (" << point.up_vector.x << ", " << point.up_vector.y << ", " << point.up_vector.z << "), ";
                std::cout << "Forward Vector: (" << point.forward_vector.x << ", " << point.forward_vector.y << ", " << point.forward_vector.z << "), ";
                std::cout << "Right Vector: (" << point.right_vector.x << ", " << point.right_vector.y << ", " << point.right_vector.z << "), ";
                std::cout << "Lane Width: " << point.lane_width << std::endl;
            }

        }
       
        std::cout << std::endl;
    }
}

const std::vector<Lane>& MapData::getLanes() const {
    return lanes;
}

void MapData::ComputeLaneLength(Lane& lane) {
    lane.length = 0.0f;
    for (size_t i = 0; i < lane.points.size() - 1; ++i) {
        lane.length += glm::distance(lane.points[i].location, lane.points[i + 1].location);
    }
}
