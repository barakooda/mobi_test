#include "DFS.h"
#include <glm/glm.hpp>

PathFinderDFS::PathFinderDFS(const Graph& graph, float minimumPathLength)
    : graph(graph), minimumPathLength(minimumPathLength) {}

std::vector<Path> PathFinderDFS::findPaths(int startingLaneId, int startingPointIndex) {
    Path initialPath;
    searchPaths(startingLaneId, startingPointIndex, 0, initialPath);
    return foundPaths;
}

void PathFinderDFS::searchPaths(int currentLaneId, int currentPointIndex, float currentPathLength, Path& currentPath) {
    auto currentNode = graph.getNode(currentLaneId);
    const auto& lanePoints = currentNode->getLane().getPoints();

    for (int i = currentPointIndex; i < lanePoints.size(); ++i) {
        currentPath.addPoint(lanePoints[i]);

        if (i > currentPointIndex) {
            currentPathLength += glm::distance(lanePoints[i - 1], lanePoints[i]);
        }

        if (i == lanePoints.size() - 1) {  // Check if it's the last point in the lane
            for (const auto& successor : currentNode->getSuccessors()) {
                int successorLaneId = successor->getLane().getId();
                if (visitedPointsMap[successorLaneId].find(0) == visitedPointsMap[successorLaneId].end()) {
                    searchPaths(successorLaneId, 0, currentPathLength, currentPath);
                }
            }
        }

        if (currentPathLength >= minimumPathLength) {
            foundPaths.push_back(currentPath);
            return;
        }

        currentPath.removeLastPoint();
        if (i > currentPointIndex) {
            currentPathLength -= glm::distance(lanePoints[i - 1], lanePoints[i]);
        }
    }

    visitedPointsMap[currentLaneId].erase(currentPointIndex);
}
