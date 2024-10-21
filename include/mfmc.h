#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <map>
#include <set>

class  Graph_mfmc
{
private:
    int V;//node number
    std::vector<std::vector<int>> edge_capacity;
    std::vector<std::vector<int>> adj;

    std::unordered_map<std::string, int> vertexIndex; // 字符串到顶点索引的映射
    std::unordered_map<int, std::string> indexVertex; // 顶点索引到字符串的映射

public:
    void addEdge(int from, int to);
    void makeGraph(std::vector<int>& shock_location, std::unordered_map<std::string,std::vector<std::string>>& gates,
                std::map<int, std::set<std::string>>& gate_set,const std::string filename);
    void matchVertex(std::vector<int>& shock_location, std::unordered_map<std::string,std::vector<std::string>>& gates,
                std::map<int, std::set<std::string>>& gate_set);

    void tarjan();

};
