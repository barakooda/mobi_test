#include "mobi_test/Graph.h"
#include <iostream>

void Graph::addLaneAsNode(const Lane& lane) {
    // Create a new node for the lane if it doesn't exist
    if (nodes.find(lane.id) == nodes.end()) {
        nodes[lane.id] = std::make_shared<Node>(lane);
    }

    std::shared_ptr<Node> currentNode = nodes[lane.id];

    // Connect predecessors to this node
    for (int pred_id : lane.predecessor_ids) {
        if (nodes.find(pred_id) == nodes.end()) {
            nodes[pred_id] = std::make_shared<Node>(Lane{pred_id, {}, {}, {}, 0.0f});
        }
        std::shared_ptr<Node> predNode = nodes[pred_id];
        currentNode->addPredecessor(predNode.get());
        predNode->addSuccessor(currentNode.get());
    }

    // Connect this node to successors
    for (int succ_id : lane.successor_ids) {
        if (nodes.find(succ_id) == nodes.end()) {
            nodes[succ_id] = std::make_shared<Node>(Lane{succ_id, {}, {}, {}, 0.0f});
        }
        std::shared_ptr<Node> succNode = nodes[succ_id];
        currentNode->addSuccessor(succNode.get());
        succNode->addPredecessor(currentNode.get());
    }
}

std::shared_ptr<Node> Graph::getNode(int laneId) const {
    auto it = nodes.find(laneId);
    if (it != nodes.end()) {
        return it->second;
    }
    return nullptr;
}

void Graph::printGraph() const {
    for (const auto& pair : nodes) {
        const std::shared_ptr<Node> node = pair.second;
        std::cout << "Lane " << node->getLane().id << " connects to: ";
        for (const Node* succ : node->getSuccessors()) {
            std::cout << succ->getLane().id << " ";
        }
        std::cout << std::endl;
    }
}

void convertMapDataToGraph(const MapData& mapData, Graph& graph) {
    for (const Lane& lane : mapData.getLanes()) {
        graph.addLaneAsNode(lane);
    }
}