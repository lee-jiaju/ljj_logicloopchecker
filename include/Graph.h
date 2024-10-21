#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

// 定义一个图类，用于表示网表中的逻辑门和连接关系
class Graph
{
public:
    //将节点与对应索引一一映射
    void newGraph();
    // 添加边的方法，u和v分别表示两个逻辑门
    void addEdge(const std::string &u, const std::string &v);

    // 检查图中是否存在环路，并打印环路中的信号
    bool hasCycle()const;
    
    // 辅助递归函数，用于深度优先搜索检测环路
    void detectCycle();

    void dfs(int v);

    int getNodeNum() ;

    std::vector<std::stack<int>> getAllCycles() const;

    std::string getVertexName(int index) const;

private:
    std::unordered_map<std::string, std::vector<std::string>> adj; // 邻接表表示的图,字符串映射

    int nodeNum;

    std::vector<std::vector<int>> adj_index;                // 邻接表,整数索引映射
    std::unordered_map<std::string, int> vertexIndex; // 字符串到顶点索引的映射
    std::unordered_map<int, std::string> indexVertex; // 顶点索引到字符串的映射

    std::vector<bool> marked;//标记当前索引点是否被搜索过
    std::vector<int> edgeTo; //记录了每个顶点在 DFS 树中的前一个顶点，用于追踪路径
    std::vector<bool> onStack; // 用于跟踪当前递归调用栈上的顶点

    std::vector<std::stack<int>> allCycles;//用于存储所有的cycle节点对应索引
};