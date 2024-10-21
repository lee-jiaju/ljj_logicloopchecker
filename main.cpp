#include <string>
#include <chrono>
#include <map>
#include <iostream>
#include <vector>
#include "Graph.h"
#include "findShock.h"
#include "gateInfo.h"
#include "parsing.h"
#include "writeCycletoFile.h"


int main() {

    Graph g;//parsing gate node edge to graph


    std::vector<int> shock_location;
    std::map<int, std::set<std::string>> signal_sets; //第一个表示第几个环，第二个表示环内元素(信号)
    std::map<int, std::set<std::string>> gate_sets;
    std::map<int, std::set<std::string>> gate_type_sets;
    std::map<int, std::set<std::string>> loop_other_signals;
    std::map<int, std::set<std::string>> loop_other_ports;

    std::string cmd = "../iverilog/run.sh";
    std::string output;
    runCommand(cmd,output);
    std::cout << "run cmd success!" << std::endl;

    std::unordered_map<std::string,std::vector<std::string>> gates;
    parseVerilogFile(output,g,gates);
    std::cout << "parsing netlist file success!" << std::endl;
    
    g.newGraph();
    std::string problem1 = "result_1.txt";
    writeCycleToFile(g, problem1, gates,signal_sets, gate_sets, loop_other_signals);
    std::cout << "get result 1!" << std::endl;
    
    
    const std::string filename2 = "result_2.txt";
    const std::string filename3 = "result_3.txt";
    findShock(signal_sets, gate_sets, loop_other_signals,gates,shock_location,filename2,filename3);
    std::cout << "get result 2&3" <<std::endl;
    
    return 0;
    
}





