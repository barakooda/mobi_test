#include <iostream>
#include <fstream>
#include <filesystem>
#include "mobi_test/sample.h"
#include "json/json.hpp"  // Include the JSON library
#include "utils/utils.h"  // Include the utils library
#include "mobi_test/MapData.h"  // Include the MapData class

int main() {
    std::cout << "Hello, mobi_test!" << std::endl;
    std::filesystem::path project_path = findProjectRoot(PROJECT_NAME);

    std::cout << "Project_path: " << project_path << std::endl;

    // Path to the JSON file
    std::filesystem::path jsonFilePath = project_path / "resources/data/map.json";

    MapData mapData;

    if (mapData.loadFromFile(jsonFilePath)) {
        mapData.print();
    } else {
        std::cerr << "Failed to load map data from file" << std::endl;
    }

    return 0;
}
