//
// Created by MoQing on 2024/4/16.
//

#ifndef ROMANIAMAP_NODE_H
#define ROMANIAMAP_NODE_H

#include <string>
#include <unordered_map>

using std::string;

class Node{
public:
    explicit Node(string name);

    // 获取节点名称
    string getName();
    // unsigned short getID() const;

    // 通过函数重载，添加1-4个邻居
    void addNeighbor(Node* node, int distance);
    void addNeighbor(Node* node1, int distance1, Node* node2, int distance2);
    void addNeighbor(Node* node1, int distance1, Node* node2, int distance2, Node* node3, int distance3);
    void addNeighbor(Node* node1, int distance1, Node* node2, int distance2, Node* node3, int distance3, Node* node4, int distance4);

    struct Neighbor {
        Node* node;
        int distance;
    };
    std::unordered_map<string, Neighbor> neighbors;
    bool visited = false;
    int USC_cost = 0;


private:
    string name;
    // unsigned short ID;
};

#endif //ROMANIAMAP_NODE_H
