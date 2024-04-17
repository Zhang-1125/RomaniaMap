//
// Created by MoQing on 2024/4/16.
//
#include "../headers/Node.h"

/**
 * Node类的构造函数
 * 用于创建一个带有指定名称、高度和邻居数量的Node实例
 *
 * @param name 节点的名称，类型为string
 * @param h 节点的高度，类型为int
 * @param neighbor_num 节点的邻居数量，类型为int
 */
Node::Node(string name, int h, int neighbor_num) {
    this->name = name; // 设置节点名称
    this->h = h; // 设置节点高度
    this->neighbor_num = neighbor_num; // 设置节点邻居数量
}

/**
 * 获取节点的名称
 *
 * @return 返回节点的名称，类型为string
 */
string Node::getName() {
    return this->name;
}

/**
 * 获取节点的邻居数量
 *
 * @return 返回节点的邻居数量，类型为int
 */
int Node::getNeighborNum() const {
    return this->neighbor_num;
}

/**
 * 获取节点的高度
 *
 * @return 返回节点的高度，类型为int
 */
int Node::getH() const {
    return this->h;
}

