//
// Created by MoQing on 2024/4/16.
//
#include "../headers/Search.h"
#include "../headers/TreeNode.h"
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>


/**
 * 构造函数：Search
 * 功能：初始化搜索对象，包括起始点、目标点和读取城市信息文件
 * 参数：
 *   - start: string类型，表示搜索的起始点
 *   - goal: string类型，表示搜索的目标点
 *   - ss: const string&类型，表示城市信息文件的路径
 */
Search::Search(string start, string goal, const string& ss) {
    this->start = start; // 设置起始点
    this->goal = goal; // 设置目标点
    std::ifstream f;      // 创建文件流用于读取城市信息文件
    f.open(ss,std::ios_base::in);
    if (!f.is_open()) {   // 检查文件是否成功打开
        std::cerr<<"File open error!"<<std::endl;
    }
    f >> state_num;      // 读取城市总数
    string name;
    int h;
    int neighbor_num;
    for(int i = 0 ; i < state_num ; i++){   // 遍历所有城市，读取并初始化城市信息
        f >> name;
        f >> h;
        f >> neighbor_num;
        Node* tempNode = new Node(name,h,neighbor_num); // 创建一个新的城市节点
        for (int j=0; j<neighbor_num; j++){  // 读取该城市的邻居城市及其距离
            f >> tempNode->nextState[j].first;
            f >> tempNode->nextState[j].second;
        }
        graph.emplace(name,tempNode); // 将城市节点添加到图中
        explored[tempNode->getName()] = false; // 标记该城市为未探索
    }
    f.close(); // 关闭文件流
}



/**
 * 对给定的树结构进行遍历，查找并输出与指定名称匹配的节点及其父节点的名称和值。
 * @param c 指向当前遍历节点的指针。
 * @param s 需要查找的节点名称。
 */
void Route(TreeNode* tn, string s){
    // 检查当前节点是否是目标节点
    if(tn->node->getName() == s){
        std::cout<<tn->node->getName()<<" v:"<<tn->value<<" -> ";
        return;
    }
    // 递归向上查找父节点
    Route(tn->father,s);
    std::cout<<tn->node->getName()<<" v:"<<tn->value<<" -> ";
}


/**
 * 实现广度优先搜索（BFS）算法。
 * 该方法不需要参数，也没有返回值。它在类的上下文中运行，需要确保类中有合适的成员变量，
 * 如图的表示、起始点和目标点等。
 */
void Search::BFS() {
    std::cout<<"----------------------------BFS----------------------------"<<std::endl;
    // 创建起始节点，并初始化搜索树的根节点和队列
    Node* startNode = graph[start];
    TreeNode* root = new TreeNode();
    std::queue<TreeNode*> Q;
    root->node = startNode;
    Q.push(root);

    // 循环搜索直到队列为空
    while(!Q.empty()){
        // 从队列中取出当前节点
        TreeNode* current = Q.front();
        Q.pop();
        Node* currentNode = current->node;

        // 打印当前节点信息
        std::cout<<"NodeName: "<<currentNode->getName()
                 <<"\tCost: "<<current->value
                 <<std::endl;
        // 标记当前节点为已探索
        explored[currentNode->getName()] = true;

        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        // 如果当前节点是目标节点，则找到路径并打印
        if(currentNode->getName() == goal){
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start);
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return;
        }

        // 遍历当前节点的所有邻居节点
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;          // 获取邻居节点的名称
            TreeNode* current_child = new TreeNode();                       // 创建一个新的树节点用于表示当前节点的子节点
            current_child->node = graph[nextNodeName];                          // 为新创建的树节点设置其对应的图中的节点
            current_child->value = current->value + currentNode->nextState[i].second;           // 计算新节点的值，即当前节点的值加上到该邻居节点的转移代价
            current_child->father = current;                                // 设置当前节点为新节点的父节点
            current->child[current->child_num] = current_child;             // 将新节点添加到当前节点的子节点列表中
            current->child_num++;                               // 更新当前节点的子节点数量

            // 打印邻居节点信息
            std::cout<< "\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;

            // 如果邻居节点未被探索，则将其加入队列
            if(explored[nextNodeName] == 0){
                Q.push(current_child);
            }
        }
        std::cout<<std::endl;
    }
    // 如果搜索完成队列为空仍未找到目标节点，则打印未找到目标信息
    std::cout << "Goal not found!" << std::endl;
    delete root;
    resetExplored();
}


/**
 * 深度优先搜索（DFS）遍历图。
 * 该方法不需要参数，通过遍历图找到目标节点，并输出从起始节点到目标节点的路径。
 * 注意：该实现假设图是通过一个邻接表（graph）来表示，其中start和goal是节点名称。
 */
void Search::DFS() {
    std::cout<<"----------------------------DFS----------------------------"<<std::endl;
    // 初始化起始节点和根节点
    Node* startNode = graph[start];
    TreeNode* root = new TreeNode();
    std::stack<TreeNode*> S;
    root->node = startNode;
    S.push(root);

    while(!S.empty()){
        // 从栈中获取当前探索的节点
        TreeNode* current = S.top();
        S.pop();
        Node* currentNode = current->node;

        // 输出当前节点信息
        std::cout << "NodeName: "<<currentNode->getName()
                  <<"\tCost: "<<current->value
                  <<"\tDepth: "<<current->depth
                  <<std::endl;

        // 标记当前节点为已探索
        explored[currentNode->getName()] = true;
        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        // 如果当前节点是目标节点，则输出路径并结束搜索
        if(currentNode->getName() == goal){
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start);
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return;
        }

        // 遍历当前节点的所有邻居节点
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;
            TreeNode* current_child = new TreeNode();
            current_child->node = graph[nextNodeName];
            current_child->value = current->value + currentNode->nextState[i].second;
            current_child->father = current;
            current_child->depth = current->depth + 1;
            current->child[current->child_num] = current_child;
            current->child_num++;

            // 输出邻居节点信息
            std::cout<<"\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;

            // 如果邻居节点未被探索，则将其压入栈中继续探索
            if(explored[nextNodeName] == 0){
                S.push(current_child);
            }
        }
        std::cout<<std::endl; // 输出换行符，使输出整洁
    }
    // 如果没有找到目标节点，则输出未找到目标的提示信息
    std::cout<<"Goal not found!"<<std::endl;
    resetExplored();
    delete root;
}


/**
 * 对给定的节点队列进行排序
 * @param q 输入的节点队列，队列中的节点值不一定有序
 * @return 经过排序后的节点队列，队列中的节点值按升序排列
 */
std::queue<TreeNode*> sort(std::queue<TreeNode*> q){
    std::queue<TreeNode*> qq; // 用于存储排序后的节点队列
    std::unordered_map<double, TreeNode*> um; // 用于辅助排序的哈希表，键为节点值加上一个小的增量，值为指向节点的指针
    int i=0;
    // 遍历输入队列，将节点按值存储到哈希表中以辅助排序
    while(!q.empty()){
        i++;
        TreeNode* t = q.front();
        q.pop();
        // 如果哈希表中该节点值对应的项为空，则直接存储
        if(um[t->value] == NULL)
            um[t->value] = t;
        else{
            // 如果哈希表中已存在该节点值，则通过给节点值加上一个小的增量来避免冲突
            um[t->value + i * 0.01] = t;
        }
    }
    // 将哈希表中的即节点值从小到大放入排序后的队列
    for(auto & mit : um)
        qq.push(mit.second);
    return qq;
}

/**
 * 使用统一成本搜索（UCS）算法寻找从起点到目标点的最短路径。
 * 该函数不接受参数，也不返回任何值，但要求类成员变量graph和explored已经被适当地初始化。
 * start和goal是起点和目标点的标识符，分别在graph中查找对应的Node。
 */
void Search::UCS() {
    std::cout<<"----------------------------UCS----------------------------"<<std::endl;
    // 初始化起始节点和搜索树的根节点
    Node* startNode = graph[start];
    TreeNode* root = new TreeNode();
    std::queue<TreeNode*> Q;
    root->node = startNode;
    Q.push(root);

    // 循环搜索直到队列为空
    while(!Q.empty()){
        // 出队并处理当前节点
        TreeNode* current = Q.front();
        Q.pop();
        Node* currentNode = current->node;

        // 打印当前节点信息
        std::cout<<"NodeName: "<<currentNode->getName()<<"\tCost: "<<current->value<<std::endl;

        // 标记当前节点为已探索
        explored[currentNode->getName()] = true;
        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        // 如果当前节点是目标节点，则找到路径，打印路径和结束信息
        if(currentNode->getName() == goal){
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start);
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return;
        }

        // 遍历当前节点的所有邻居节点
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;
            TreeNode* current_child = new TreeNode();
            current_child->node = graph[nextNodeName];
            current_child->value = current->value + currentNode->nextState[i].second;
            current_child->father = current;
            current->child[current->child_num] = current_child;
            current->child_num++;

            // 打印邻居节点信息
            std::cout<<"\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;

            // 如果邻居节点未被探索，则将其入队
            if(explored[nextNodeName] == 0){
                Q.push(current_child);
            }
        }
        // 对队列进行排序，确保总是扩展代价最小的节点
        Q = sort(Q);
        std::cout<<std::endl;
    }
    // 如果队列为空仍未找到目标，打印目标未找到信息
    std::cout<<"Goal not found!"<<std::endl;
    delete root;
    resetExplored();
}


/**
 * 使用IDDFS（迭代加深搜索）算法寻找从起始节点到目标节点的路径。
 * @param D 搜索深度限制。
 * @return 如果找到目标节点返回1，否则返回0。
 */
int Search::IDDFS(int D) {
    std::cout<<"---------------------------IDDFS---------------------------"<<std::endl;
    Node* startNode = graph[start];
    TreeNode* root = new TreeNode(); // 创建根结点
    std::stack<TreeNode*> S; // 使用栈存储待搜索的结点
    root->node = startNode;
    S.push(root);
    while(!S.empty()){
        TreeNode* current = S.top();
        S.pop();
        if(current->depth>D){ // 如果当前深度超过限制，则跳过
            continue;
        }

        // 输出当前节点信息
        Node* currentNode = current->node;
        std::cout<<"NodeName: "<<currentNode->getName()
                 <<"\tCost: "<<current->value
                 <<"\tDepth: "<<current->depth
                 <<std::endl;
        explored[currentNode->getName()] = true; // 标记当前节点为已探索
        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        if(currentNode->getName() == goal){ // 如果找到目标节点
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start); // 输出路径
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return 1;
        }

        // 遍历当前节点的所有邻居节点
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;
            TreeNode* current_child = new TreeNode(); // 创建邻居节点的搜索结点
            current_child->node = graph[nextNodeName];
            current_child->value = current->value + currentNode->nextState[i].second;
            current_child->father = current;
            current_child->depth = current->depth + 1;
            current->child[current->child_num]= current_child;
            current->child_num++;

            // 输出邻居节点信息
            std::cout<<"\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;
            if(explored[nextNodeName] == 0){ // 如果邻居节点未被探索，则加入搜索栈
                S.push(current_child);
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"Goal not found!"<<std::endl; // 如果未找到目标节点
    delete root;
    resetExplored();
    return 0;
}


/**
 * @struct Compare 用于比较两个TreeNode指针的结构体
 */
struct Compare{
    /**
     * @brief 重载的运算符()，用于比较两个TreeNode指针所指向的节点的值
     * @param a 指向第一个TreeNode节点的指针
     * @param b 指向第二个TreeNode节点的指针
     * @return 如果a指向的节点的值大于b指向的节点的值，则返回true；否则返回false。
     */
    bool operator()(TreeNode* a, TreeNode* b){
        return a->value > b->value; // 比较两个节点的值并返回比较结果
    }
};

/**
 * 实现广度优先搜索（GBFS）算法。
 * 该函数不接受参数，也不返回任何值。它在给定的图中从起始节点开始搜索，直到找到目标节点或遍历完所有可达节点。
 * 在搜索过程中，会打印每个被探索的节点及其到起始节点的代价。
 */
void Search::GBFS() {
    std::cout<<"----------------------------GBFS----------------------------"<<std::endl;
    // 初始化起始节点和搜索树的根节点
    Node* startNode = graph[start];
    TreeNode* root = new TreeNode();
    // 使用优先队列来按照节点的代价排序
    std::priority_queue<TreeNode*,std::vector<TreeNode*>,Compare> Q;
    root->node = startNode;
    root->value = startNode->getH();
    Q.push(root);

    // 当优先队列不为空时持续搜索
    while(!Q.empty()){
        // 从队列中获取当前代价最小的节点
        TreeNode* current = Q.top();
        Q.pop();
        Node* currentNode = current->node;
        // 打印当前节点信息
        std::cout<<"NodeName: "<<currentNode->getName()
                 <<"\tCost: "<<current->value
                 <<std::endl;

        // 标记当前节点为已探索
        explored[currentNode->getName()] = true;
        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        // 如果当前节点是目标节点，则找到路径并打印
        if(currentNode->getName() == goal){
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start);
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return;
        }

        // 遍历当前节点的所有邻居节点
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;
            TreeNode* current_child = new TreeNode();
            current_child->node = graph[nextNodeName];
            current_child->value = graph[nextNodeName]->getH();
            current_child->father = current;
            current->child[current->child_num] = current_child;
            current->child_num++;

            // 打印邻居节点信息
            std::cout<<"\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;
            // 如果邻居节点未被探索，则将其加入优先队列
            if(explored[nextNodeName] == 0){
                Q.push(current_child);
            }
        }
        std::cout<<std::endl;
    }
    // 如果没有找到目标节点，则打印未找到目标信息
    std::cout<<"Goal not found!"<<std::endl;
    delete root;
    resetExplored();
}

/**
 * 实现A*搜索算法。
 * 该函数不接受参数，也不返回任何值。它通过优先队列来搜索从起始节点到目标节点的最短路径。
 * 在搜索过程中，使用了A*算法的启发式函数来指导搜索。
 */
void Search::AStar() {
    std::cout<<"----------------------------A*----------------------------"<<std::endl;
    // 获取起始节点
    Node* startNode = graph[start];
    // 创建根结点
    TreeNode* root = new TreeNode();
    // 使用优先队列来存储待搜索的节点，队列中的节点根据其值（即启发式函数值）进行排序
    std::priority_queue<TreeNode*,std::vector<TreeNode*>,Compare> Q;
    // 初始化根节点，并将其加入到优先队列中
    root->node = startNode;
    root->value = startNode->getH();
    Q.push(root);

    // 当优先队列不为空时循环执行搜索
    while(!Q.empty()){
        // 从队列中取出当前价值最高的节点
        TreeNode* current = Q.top();
        Q.pop();
        // 输出当前节点信息
        Node* currentNode = current->node;
        std::cout<<"NodeName: "<<currentNode->getName()
                 <<"\tCost: "<<current->value
                 <<std::endl;

        // 标记当前节点为已探索
        explored[currentNode->getName()] = true;
        std::cout << "\tSearch set (Visited Nodes):" << std::endl;
        for (const auto& entry : explored) {
            if (entry.second) { // 只打印值为true的条目
                std::cout << "\t\t" << entry.first << std::endl;
            }
        }
        std::cout << std::endl;

        // 如果当前节点是目标节点，则找到路径，输出路径信息
        if(currentNode->getName() == goal){
            std::cout<<"Goal found!"<<std::endl;
            Route(current,start);
            std::cout<<"end"<<std::endl;

            delete root;
            resetExplored();
            return;
        }

        // 遍历当前节点的所有邻居节点，为每个未探索的邻居节点创建新的树节点，并加入到优先队列中
        for(int i = 0;i<currentNode->getNeighborNum();i++){
            string nextNodeName = currentNode->nextState[i].first;
            TreeNode* current_child = new TreeNode();
            current_child->node = graph[nextNodeName];
            // 计算新节点的值
            current_child->value = current->value - currentNode->getH() + currentNode->nextState[i].second + graph[nextNodeName]->getH();
            current_child->father = current;
            current->child[current->child_num] = current_child;
            current->child_num++;

            // 输出新节点信息
            std::cout<<"\tSuccessor Node: "<<nextNodeName
                     <<" \tCost: "<<current_child->value
                     <<" \tState: "<<explored[nextNodeName]
                     <<std::endl;
            // 如果邻居节点未被探索，则将其加入到优先队列中
            if (explored[nextNodeName] == 0){
                Q.push(current_child);
            }
        }
        std::cout<<std::endl;
    }
    // 如果搜索完成时仍未找到目标节点，则输出未找到目标的信息
    std::cout<<"Goal not found!"<<std::endl;
    delete root;
    resetExplored();
}

void Search::resetExplored() {
    for (auto& entry : explored) {
        entry.second = false;
    }
}
