//
// Created by MoQing on 2024/4/16.
//

#ifndef ROMANIAMAP_NODE_H
#define ROMANIAMAP_NODE_H

#include <string>
#include <unordered_map>

using std::string;
typedef std::pair<string, int> neighbor;

class Node{
public:
    explicit Node(string name, int h, int neighbor_num);

    string getName();                 // 获取节点名称
    int getNeighborNum() const;         // 获取节点的邻居节点个数
    int getH() const;              // 获取节点的h值

    std::unordered_map<int,neighbor> nextState;

private:
    string name;
    int neighbor_num;
    int h;
};

#endif //ROMANIAMAP_NODE_H
