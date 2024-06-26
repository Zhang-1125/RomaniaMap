# RomaniaMap
## 罗马尼亚地图路径搜索问题
### 说明
本项目为课程作业。作业基于经典的罗马尼亚地图问题，要求分别利用**宽度/广度优先搜索（BFS）**、**深度优先搜索（DFS）**、**一致代价搜索（UCS）**、**贪婪最佳优先搜索（GBFS）**和**A*搜索**五种算法，搜索从`Zerind`到`Bucharest`的路径，并比较搜索结果分析算法的性能。
### 思路
该问题实际上是一个利用不同算法对图遍历的问题，整个图是一个无向有权的完全图，边的权重即为代价（cost）。

为了解决该问题，构建一下几个类：
1. `Node`类，该类包含城市的名称、到达`Bucharest`的代价、以及邻居节点。邻居节点使用C++标准模板库（Standard Template Library，STL）中提供的`unordered_map`容器存储，因为该关联容器使用哈希表作为底层实现，所以可以快速查找到指定节点。
2. `TreeNode`类，作为搜索过程中的节点存储。其包含子节点的数量，到达当前节点的代价，当前搜索深度，指向对应`Node`的指针，指向父节点的`TreeNode`指针，以及使用`unordered_map`容器存储的孩子节点的`TreeNode`指针。
3. `Search`类，作为搜索算法的具体实现。包含存储起点和终点名称的字符串，总城市数目（用于读取输入文件），以及通过`unordered_map`存储的所有城市的信息和以探索过的城市。提供六种方法，通过六种不同算法实现路径搜索。
4. `Run`类，负责在命令行界面中提供搜索算法的选择和运行，提供展示菜单和获取选项的方法。

### 使用
提供一个`Search`类，其中有提供六种不同的搜索算法，调用这些方法将输出逐步的搜索过程，最终输出寻找到的路径。
```
void BFS();         // 广度优先搜索
void DFS();         // 深度优先搜索
void UCS();         // 一致代价搜索
int IDDFS(int x);   // 迭代加深搜索（x为深度）
void GBFS();        // 贪婪搜索
void AStar();       // A*搜索
```
Search类的构造函数需要提供两个string类型的参数作为起点和终点，以及一个存储地图信息的文本文档。
```
Search search("Zerind", "Bucharest", "sample.txt")
```
提供一个`Run`类，负责在命令行界面中提供搜索算法的选择和运行。
### 示例
```
#include "headers/Search.h"
#include "headers/Run.h"

int main() {
    Search search("Zerind","Bucharest","Romania.txt");
    Run run(&search);
    while (true){
        run.showMenu();
        run.getChoice();
    }
}
```
输出：
```
-----------------------RomaniaMap-----------------------
Please choose the algorithm you want to use:
        1.BFS
        2.DFS
        3.UCS
        4.GBFS
        5.IDDFS
        6.AStar
      -----------
        0.Exit
Please input your choice:
```
输入：
```
6
```
输出：
```
----------------------------A*----------------------------
Node name: Zerind       Value: 374
        ChildNode: Oradea       Value: 451      State: 0
        ChildNode: Arad         Value: 441      State: 0

Node name: Arad Value: 441
        ChildNode: Zerind       Value: 524      State: 1
        ChildNode: Sibiu        Value: 468      State: 0
        ChildNode: Timisoara    Value: 522      State: 0

Node name: Oradea       Value: 451
        ChildNode: Zerind       Value: 516      State: 1
        ChildNode: Sibiu        Value: 475      State: 0

Node name: Sibiu        Value: 468
        ChildNode: Oradea       Value: 746      State: 1
        ChildNode: Arad         Value: 721      State: 1
        ChildNode: Fagaras      Value: 490      State: 0
        ChildNode: RimnicuVilcea        Value: 488      State: 0

Node name: Sibiu        Value: 475
        ChildNode: Oradea       Value: 753      State: 1
        ChildNode: Arad         Value: 728      State: 1
        ChildNode: Fagaras      Value: 497      State: 0
        ChildNode: RimnicuVilcea        Value: 495      State: 0

Node name: RimnicuVilcea        Value: 488
        ChildNode: Sibiu        Value: 628      State: 1
        ChildNode: Craiova      Value: 601      State: 0
        ChildNode: Pitesti      Value: 492      State: 0

Node name: Fagaras      Value: 490
        ChildNode: Sibiu        Value: 666      State: 1
        ChildNode: Bucharest    Value: 525      State: 0

Node name: Pitesti      Value: 492
        ChildNode: Craiova      Value: 690      State: 0
        ChildNode: Bucharest    Value: 493      State: 0
        ChildNode: RimnicuVilcea        Value: 682      State: 1

Node name: Bucharest    Value: 493
Goal found!
Zerind v:374 -> Arad v:441 -> Sibiu v:468 -> RimnicuVilcea v:488 -> Pitesti v:492 -> Bucharest v:493 -> end
Press Enter to continue...

```
其中`Node name`为当前节点名称，`Value`为当前cost值，`ChildNode`为下一步可以选择的节点名称，`State`为当前节点状态（0为未被探索，1为已经探索）。

注：本项目的部分注释由AI生成，未必通顺。