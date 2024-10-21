#include "Graph.h"

void Graph::addEdge(const std::string &u, const std::string &v)
{
    adj[u].push_back(v);
    //std::cout << "success" << std::endl;
}

void Graph::newGraph(void){
    int len=0;
    int index = 0;

    nodeNum = adj.size();                     // 计算节点数量
    std::cout << nodeNum << std::endl;
    adj_index.resize(nodeNum);                // 调整 adj_index 的大小
    vertexIndex.clear();                       // 清空 vertexIndex
    indexVertex.clear();                       // 清空 indexVertex
    std::cout << "newGraph" << std::endl;
    for (auto it = adj.begin(); it != adj.end(); it++)
    {
        vertexIndex[it->first] = index;
        //std::cout << it->first << std::endl;
        
        indexVertex[index] = it->first;
        index++;
    }
    //index = 0;
    for (const auto& pair : adj)
    {
        len = pair.second.size();
        for (int j = 0; j < len; j++)
        {
            adj_index[vertexIndex[pair.first]].push_back(vertexIndex[pair.second[j]]);
            //std::cout << "vertexIndex:" << vertexIndex[pair.second[j]] << std::endl;
        }
    }
    std::cout << "match end" << std::endl;
    
}



//取得所有node数量
int Graph::getNodeNum() {
    if (nodeNum == 0)
    {
        nodeNum = adj.size();
        std::cout << nodeNum << std::endl;
    }
    return nodeNum;
}

//检测所有的环
void Graph::detectCycle()
{

    marked.resize(adj.size(), false);  // 初始化 marked
    edgeTo.resize(adj.size(), -1);     // 初始化 edgeTo
    onStack.resize(adj.size(), false); // 初始化 onStack
    std::cout << "start dfs now" << std::endl;

    for (int i = 0; i < adj.size() ; i++)
    {   
        //std::cout << "dfs times"<< i << std::endl;
        
        if (!marked[i])
        {
            dfs(i);
            //std::cout << "dfs node:" << i << std::endl;
        }
        
    }
    
}

//dfs算法
void Graph::dfs(int v){
    onStack[v] = true;
    marked[v] = true;
    //std::cout << "Visiting node " << v << std::endl;
    int i = 0;
    for (int w : adj_index[v])
    {
        if (onStack[w])
        {
            std::stack<int> cycle;
            for (int x = v; x != w; x = edgeTo[x])
            {
                cycle.push(x);
            }
            cycle.push(w);
            cycle.push(v);
            allCycles.push_back(cycle);
            //std::cout << "cycle" << i << std::endl;
            i++;

        }
        else if (!marked[w])
        {
            edgeTo[w] = v;
            dfs(w);
            //std::cout << w << std::endl;
        }
    }
    onStack[v] = false;
}

bool Graph::hasCycle() const
{
    return !allCycles.empty();
}

std::vector<std::stack<int>> Graph::getAllCycles() const
{
    return allCycles;
}


std::string Graph::getVertexName(int index) const {
    auto it = indexVertex.find(index);
    if (it != indexVertex.end()) {
        return it->second;
    }
    return ""; // Return an empty string if index is not found
}

