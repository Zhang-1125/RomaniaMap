//
// Created by MoQing on 2024/4/16.
//

#ifndef ROMANIAMAP_SEARCH_H
#define ROMANIAMAP_SEARCH_H

#include "Node.h"

class Search{
public:
    Search(string start, string goal);

    void Init(const string& ss);

    void BFS();         // 广度优先搜索
    void DFS();         // 深度优先搜索
    void UCS();         // 一致代价搜索
    int IDDFS(int x);   // 迭代加深搜索
    void GBFS();        // 贪婪搜索
    void AStar();       // A*搜索

private:
    string start;
    string goal;

    int state_num = 0;          // 总城市数目
    std::unordered_map<string, Node*> graph;     // 存储罗马尼亚问题所有城市的信息
    std::unordered_map<string, bool> explored;     // 存储已经探索过的城市

};

#endif //ROMANIAMAP_SEARCH_H
