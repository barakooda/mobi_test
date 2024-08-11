#pragma once

#include <vector>
#include <map>
#include <set>
#include "Graph.h"
#include "Path.h"

class PathFinderDFS {
public:
    PathFinderDFS(const Graph& graph, float minimumPathLength);

    std::vector<Path> findPaths(int startingLaneId, int startingPointIndex);

private:
    void searchPaths(int currentLaneId, int currentPointIndex, float currentPathLength, Path& currentPath);

    const Graph& graph;
    float minimumPathLength;
    std::map<int, std::set<int>> visitedPointsMap;
    std::vector<Path> foundPaths;
};
