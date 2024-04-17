//
// Created by MoQing on 2024/4/17.
//
#include "../headers/TreeNode.h"

/**
 * TreeNode类的构造函数
 * 用于创建一个空的树节点对象，并对其进行初始化。
 *
 * 参数：无
 * 返回值：无
 */
TreeNode::TreeNode() {
    this->child_num = 0;             // 初始化孩子节点数量为0
    this->value = 0;               // 初始化节点的启发式搜索代价估计值为0
    this->depth = 0;               // 初始化节点的深度为0
    this->father = nullptr;          // 初始化节点的父亲节点为空指针
    this->child.clear();             // 初始化孩子的集合为空
}
