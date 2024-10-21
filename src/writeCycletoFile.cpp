#include "writeCycletoFile.h"
//参数中all_gates为记录所有门信息的映射，传入实参应为gates，函数中gates为一个门集合，局部变量
void writeCycleToFile(Graph &G, const std::string filename, std::unordered_map<std::string, std::vector<std::string>>& all_gates,std::map<int, std::set<std::string>> &signal_sets, std::map<int, std::set<std::string>> &gate_sets,
std::map<int, std::set<std::string>> &other_signal_sets){
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::cout << "start detect cycle" << std::endl;
    G.detectCycle();
    std::cout << "finish detect cycle" << std::endl;

    std::cout << G.hasCycle() << std::endl;
    if (G.hasCycle())
    {
        
        int circle_flag = 0;
        std::vector<std::stack<int>> cycles = G.getAllCycles();
        for (const auto &cycle : cycles)
        {
            std::set<std::string> signals;
            std::set<std::string> gates;
            std::set<std::string> other_signals;
            //std::set<std::string> other_ports;

            std::stack<int> tempCycle1 = cycle;
            std::stack<int> tempCycle2 = cycle;
            //std::stack<int> tempCycle3 = cycle;

            circle_flag++;

            while (!tempCycle1.empty())
            {
                int v = tempCycle1.top();
                tempCycle1.pop();
                std::string vertexName = G.getVertexName(v);

                if (vertexName[0] == 'w')
                {
                    signals.insert(vertexName);
                }
            }

            while (!tempCycle2.empty())
            {
                int v = tempCycle2.top();
                tempCycle2.pop();
                std::string vertexName = G.getVertexName(v);

                std::string gateName = vertexName;
                std::string portNumber;
                

                if (vertexName[0] == 'I')
                {
                    std::vector<std::string>& gate_info = all_gates[vertexName];
                    if (gate_info[0] != "not1" )
                    {
                        if (signals.find(gate_info[2])!= signals.end()){
                            portNumber = "port1";
                            other_signals.insert(gate_info[3]);
                            //other_ports.insert(gateName + "." + "port2");
                        }
                        else{
                            portNumber = "port2";
                            other_signals.insert(gate_info[2]);
                            //other_ports.insert(gateName + "." + "port1");
                        }
                    }
                    else{
                        portNumber = "port1";
                    }
                    gates.insert(gateName + "." + portNumber);

                }
            }

            if (!signals.empty())
            {
                outFile << circle_flag << ")\n";

                outFile << "  Loop Signals: ";
                auto it = signals.begin();
                outFile << *it;

                ++it;
                for (; it != signals.end(); ++it)
                {
                    outFile << ", " << *it;
                }
                outFile << std::endl;
            }

            if (!gates.empty())
            {
                outFile << "  Loop Gates: ";
                auto it = gates.begin();
                outFile << *it;

                ++it;
                for (; it != gates.end(); ++it)
                {
                    outFile << ", " << *it;
                }
                outFile << std::endl;
            }
            //此处可尝试优化将cycle中的信号、门、其他信号的存入改为上面的循环中执行
            //std::cout << circle_flag << std::endl;
            for (const auto &signal : signals)
            {
                signal_sets[circle_flag].insert(signal);
            }

            for (const auto &gate : gates)
            {
                gate_sets[circle_flag].insert(gate);
            }
            for (const auto &other_signal : other_signals)
            {
                other_signal_sets[circle_flag].insert(other_signal);
            }
            /*** 
            for (const auto &other_port : other_ports)
            {
                loop_other_ports[circle_flag].insert(other_port);
                std::cout << "other port" << other_port << std::endl;
            }
            ***/
            
        }
    }
    else
    {
        outFile << "No cycle detected." << std::endl;
    }

    outFile.close();
}
