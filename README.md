# RomaniaMap
## 罗马尼亚地图路径搜索问题
说明：本项目为课程作业
作业基于经典的罗马尼亚地图模型，要求分别利用宽度/广度优先搜索(BFS)、深度优先搜索(DFS)、一致代价搜索、贪婪最佳优先搜索和A*搜索五种算法，搜索从Zerind到Bucharest的路径，并比较搜索结果分析算法的性能。
### 使用
提供一个`Search`类，其中有提供六种不同的搜索算法，调用这些方法将输出逐步的搜索过程，最终输出寻找到的路径。
```
void BFS();         // 广度优先搜索
void DFS();         // 深度优先搜索
void UCS();         // 一致代价搜索
int IDDFS(int x);   // 迭代加深搜索
void GBFS();        // 贪婪搜索
void AStar();       // A*搜索
```
Search类的构造函数需要提供两个string类型的参数作为起点和终点，以及一个存储地图信息的文本文档。
```
Search search("Zerind", "Bucharest", "sample.txt")
```
