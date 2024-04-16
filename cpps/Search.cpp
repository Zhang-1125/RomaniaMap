//
// Created by MoQing on 2024/4/16.
//
#include "../headers/Search.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_set>

Search::Search(Node *startNode, Node *endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}

void Search::BFS() {
    std::queue<Node*> toExplore;
    std::unordered_map<string, Node*> predecessors;
    std::vector<Node*> openList;            // 开节点表
    std::vector<Node*> searchList;          // 搜索节点表
    toExplore.push(startNode);

    Node* currentNode = startNode;
    startNode->visited = true;

    while (currentNode != endNode){
        for (auto & neighbor : currentNode->neighbors){
            if (neighbor.second.node->visited)
                continue;
            toExplore.push(neighbor.second.node);
            neighbor.second.node->visited = true;
        }
        toExplore.pop();
        currentNode = toExplore.front();
        std::cout << currentNode->getName() << std::endl;
    }
}

void Search::DFS() {
    std::stack<Node*> toExplore;

    Node* currentNode = startNode;
    toExplore.push(currentNode);
    currentNode->visited = true;

    while (currentNode != endNode){
        currentNode = toExplore.top();

        for (auto & neighbor : currentNode->neighbors){
            if (!neighbor.second.node->visited) {
                neighbor.second.node->visited = true;
                toExplore.push(neighbor.second.node);
                break;
            }
        }

        if (currentNode == toExplore.top()){
            toExplore.pop();
        }
        std::cout << currentNode->getName() << std::endl;
    }

}
