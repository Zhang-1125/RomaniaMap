//
// Created by MoQing on 2024/4/16.
//

#ifndef ROMANIAMAP_SEARCH_H
#define ROMANIAMAP_SEARCH_H

#include <stack>
#include <vector>
#include "Node.h"

class Search{
public:
    Search(Node* startNode, Node* endNode);

    void BFS();         // 广度优先搜索
    void DFS();         // 深度优先搜索
    void UCS();         // 一致代价搜索
    void GBFS();        // 贪婪搜索
    void AStar();       // A*搜索

private:
    Node* startNode;
    Node* endNode;



};

#endif //ROMANIAMAP_SEARCH_H
