
#ifndef NODE_H
#define NODE_H

#include <unordered_set>
#include "mobi_test/Lane.h"

class Node {
public:
    Node(const Lane& lane);

    void addPredecessor(Node* pred);
    void addSuccessor(Node* succ);

    const Lane& getLane() const;
    const std::unordered_set<Node*>& getPredecessors() const;
    const std::unordered_set<Node*>& getSuccessors() const;

private:
    Lane lane;
    std::unordered_set<Node*> predecessors;
    std::unordered_set<Node*> successors;
};

#endif // NODE_H
