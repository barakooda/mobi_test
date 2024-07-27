#include "mobi_test/PathGraph.h"
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <unordered_set>


PathGraph::PathGraph(const MapData& mapData) {
    buildGraph(mapData);
}

PathGraph::~PathGraph() {
    deleteGraph();
}

void PathGraph::buildGraph(const MapData& mapData) {
    // Create GraphNode objects for each lane
    for (const auto& lane : mapData.getLanes()) {
        GraphNode* node = new GraphNode(lane.id, lane.points);
        laneNodes[lane.id] = node;
        allNodes.push_back(node);
    }

    // Link GraphNode objects to their successors
    for (const auto& lane : mapData.getLanes()) {
        GraphNode* node = laneNodes[lane.id];
        for (int succId : lane.successor_ids) {
            if (laneNodes.find(succId) != laneNodes.end()) {
                node->successors.push_back(laneNodes[succId]);
            }
        }
    }
}

void PathGraph::deleteGraph() {
    for (auto node : allNodes) {
        delete node;
    }
    allNodes.clear();
    laneNodes.clear();
}

std::vector<Path> PathGraph::FindPaths(int startLaneId, int startPointIndex, float minPathLength) {
    std::vector<Path> paths;
    auto it = laneNodes.find(startLaneId);
    if (it == laneNodes.end() || startPointIndex >= static_cast<int>(it->second->points.size())) {
        return paths;
    }

    GraphNode* startNode = it->second;
    std::stack<std::pair<GraphNode*, Path>> stack;
    std::unordered_set<GraphNode*> visitedNodes;

    Path initialPath;
    initialPath.points.push_back(startNode->points[startPointIndex]);
    stack.push({startNode, initialPath});

    while (!stack.empty()) {
        auto [node, currentPath] = stack.top();
        stack.pop();

        if (visitedNodes.find(node) != visitedNodes.end()) {
            continue; // Avoid cycles
        }

        visitedNodes.insert(node);

        for (size_t i = 0; i < node->points.size(); ++i) {
            const Point& point = node->points[i];
            if (!currentPath.points.empty()) {
                const Point& lastPoint = currentPath.points.back();
                float distance = glm::distance(lastPoint.location, point.location);
                currentPath.length += distance;
            }
            currentPath.points.push_back(point);

            if (currentPath.length <= minPathLength) {
                paths.push_back(currentPath);
            }

            // Continue searching for paths
            for (GraphNode* succ : node->successors) {
                stack.push({succ, currentPath});
            }

            currentPath.points.pop_back();
            if (!currentPath.points.empty()) {
                const Point& lastPoint = currentPath.points.back();
                float distance = glm::distance(lastPoint.location, point.location);
                currentPath.length -= distance;
            }
        }

           // Only add paths that meet the minimum path length
     

        visitedNodes.erase(node);
    }

    return paths;
}