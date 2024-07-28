#ifndef MAPDATA_H
#define MAPDATA_H

#include <string>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>
#include "json/json.hpp"
#include "mobi_test/Point.h"
#include "mobi_test/Lane.h"


class MapData {
public:
    bool loadFromFile(const std::filesystem::path& filePath);
    
    void print() const;

    const std::vector<Lane>& getLanes() const; // Getter for lanes

private:
    void ComputeForwardAndRightVector(Lane& lane);
    void ComputeLaneLength(Lane& lane);
    std::vector<Lane> lanes;
};

#endif // MAPDATA_H
