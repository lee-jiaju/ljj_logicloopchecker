#include "mfmc.h"

void Graph_mfmc::addEdge(int from, int to){
    adj[from].push_back(to); // 加入邻接表
}

void Graph_mfmc::matchVertex(std::vector<int>& shock_location, std::unordered_map<std::string,std::vector<std::string>>& gates,
                std::map<int, std::set<std::string>>& gate_set){
                    
                    std::set<std::string> gate;
                    int circle_flag = gate_set.size();

                    for(int i = 0; i < circle_flag; i++){
                        if (shock_location[i])
                        {
                            for (auto it = gate_set[i+1].begin(); it != gate_set[i+1].end(); it++)
                            {
                                gate.insert(*it);
                            }
                            
                        }
                        
                    }

                    int gate_num = gate.size();
                    int index = 0;
                    for (auto it = gate.begin(); it != gate.end(); it++)
                    {
                        vertexIndex[*it] = index;
                        indexVertex[index] = *it;
                        index++;
                    }
                    
                }


void Graph_mfmc::makeGraph(std::vector<int>& shock_location, std::unordered_map<std::string,std::vector<std::string>>& gates,
                std::map<int, std::set<std::string>>& gate_set,const std::string filename){
                    int circle_flag = gate_set.size();

                    for(int i = 0; i < circle_flag; i++){
                        if (shock_location[i])
                        {
                            for (auto it = gate_set[i+1].begin(); it != gate_set[i+1].end(); it++)
                            {   
                                auto next = std::next(it);
                                if (next != gate_set[i+1].end())
                                {
                                    addEdge(vertexIndex[*it],vertexIndex[*next],1);
                                }
                                else
                                {
                                    addEdge(vertexIndex[*it],vertexIndex[*(gate_set[i+1].begin())]);
                                }
                                
                            }
                            
                        }
                        
                    }  
}

void Graph_mfmc::tarjan(){

}
