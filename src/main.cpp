#include <iostream>
#include <fstream>
#include <filesystem>
#include "json/json.hpp"  // Include the JSON library
#include "utils/utils.h"  // Include the utils library
#include "mobi_test/MapData.h"  // Include the MapData class
#include "mobi_test/Graph.h"  // Include the Graph class
#include "mobi_test/SaveMapData.h"  // Include the function to save MapData to a file

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

    // Create a Graph object
    Graph graph;

    // Convert the MapData object to a Graph object
    convertMapDataToGraph(mapData, graph);

    // Print the Graph object
    graph.printGraph();

    //to find paths in the lane graph, with min required length
    //path begins at a specific lane point and may traverse multiple lanes, but it must follow the successors/predecessors connections defined in the map
    //If a path contains cycles, don’t return it.

    // Find paths in the lane graph
    



    // Save the MapData object to a new JSON file
    std::filesystem::path outputFilePath = project_path / "resources/data/enhanced_map.json";
    if (!saveMapDataToFile(mapData, outputFilePath)) {
        std::cerr << "Failed to save map data to file" << std::endl;
        return 1;
    }

    std::cout << "Map data saved successfully to " << outputFilePath << std::endl;

    return 0;
}
