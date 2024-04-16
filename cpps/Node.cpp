//
// Created by MoQing on 2024/4/16.
//
#include "../headers/Node.h"

Node::Node(string name) {
    this->name = name;
}

string Node::getName() {
    return this->name;
}

void Node::addNeighbor(Node* node, int distance) {
    neighbors.emplace(node->getName(), Neighbor{node,distance});
}

void Node::addNeighbor(Node *node1, int distance1, Node *node2, int distance2) {
    neighbors.emplace(node1->getName(), Neighbor{node1,distance1});
    neighbors.emplace(node2->getName(), Neighbor{node2,distance2});
}

void Node::addNeighbor(Node *node1, int distance1, Node *node2, int distance2, Node *node3, int distance3) {
    neighbors.emplace(node1->getName(), Neighbor{node1,distance1});
    neighbors.emplace(node2->getName(), Neighbor{node2,distance2});
    neighbors.emplace(node3->getName(), Neighbor{node3,distance3});
}

void Node::addNeighbor(Node *node1, int distance1, Node *node2, int distance2, Node *node3, int distance3, Node *node4,
                       int distance4) {
    neighbors.emplace(node1->getName(), Neighbor{node1,distance1});
    neighbors.emplace(node2->getName(), Neighbor{node2,distance2});
    neighbors.emplace(node3->getName(), Neighbor{node3,distance3});
    neighbors.emplace(node4->getName(), Neighbor{node4,distance4});
}

/*
unsigned short Node::getID() const {
    return this->ID;
}
*/