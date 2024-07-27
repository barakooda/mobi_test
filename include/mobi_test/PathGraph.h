#ifndef PATHGRAPH_H
#define PATHGRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "mobi_test/MapData.h"
#include "mobi_test/Path.h"
struct GraphNode {
    int laneId;
    std::vector<Point> points;
    std::vector<GraphNode*> successors;

    GraphNode(int laneId, const std::vector<Point>& points)
        : laneId(laneId), points(points) {}
};

class PathGraph {
public:
    explicit PathGraph(const MapData& mapData);
    ~PathGraph();
    std::vector<Path> FindPaths(int startLaneId, int startPointIndex, float minPathLength);

private:
    void buildGraph(const MapData& mapData);
    void deleteGraph();
    void dfs(GraphNode* node, Path& currentPath, std::unordered_set<GraphNode*>& visitedNodes, std::vector<Path>& paths, float minPathLength);

    std::unordered_map<int, GraphNode*> laneNodes;
    std::vector<GraphNode*> allNodes;
};

#endif // PATHGRAPH_H