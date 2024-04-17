//
// Created by MoQing on 2024/4/17.
//

#ifndef ROMANIAMAP_TREENODE_H
#define ROMANIAMAP_TREENODE_H

#include "Node.h"
#include <unordered_map>

class TreeNode{
public:
    TreeNode();

    int child_num;                                  // 子节点数量
    int value;                                     // 启发式搜索种 该树节点的代价估计值
    int depth;                                      // 节点深度
    Node* node{};                                      // 该树节点对应的节点
    TreeNode* father;                                // 保存该节点的父节点
    std::unordered_map<int, TreeNode*> child;             // 保存该节点的子节点
};

#endif //ROMANIAMAP_TREENODE_H
