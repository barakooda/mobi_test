#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <memory>
#include "mobi_test/Node.h"
#include "mobi_test/MapData.h" // Updated include path

class Graph {
public:
    void addLaneAsNode(const Lane& lane);
    std::shared_ptr<Node> getNode(int laneId) const;
    void printGraph() const;

private:
    std::map<int, std::shared_ptr<Node>> nodes;
};

void convertMapDataToGraph(const MapData& mapData, Graph& graph);

#endif // GRAPH_H
