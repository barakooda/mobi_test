
#include "mobi_test/Node.h"

Node::Node(const Lane& lane) : lane(lane) {}

void Node::addPredecessor(Node* pred) {
    predecessors.insert(pred);
}

void Node::addSuccessor(Node* succ) {
    successors.insert(succ);
}

const Lane& Node::getLane() const {
    return lane;
}

const std::unordered_set<Node*>& Node::getPredecessors() const {
    return predecessors;
}

const std::unordered_set<Node*>& Node::getSuccessors() const {
    return successors;
}