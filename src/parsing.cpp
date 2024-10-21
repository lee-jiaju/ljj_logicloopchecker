#include "parsing.h"
//#include "gateInfo.h"
using namespace std;

void runCommand(const string& cmd,std::string& output) {
    //string result;
    char buffer[128];
    FILE* pipe = popen(cmd.c_str(),"r");
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            output += buffer;
    }
    pclose(pipe);
    std::cout << "try to get info" << std::endl;
    //return result;
}


// 解析简单的Verilog网表文件
void parseVerilogFile(const std::string& output, Graph &graph,std::unordered_map<std::string,std::vector<std::string>>& gates)
{
    //ifstream file(filename);
    istringstream iss(output);
    bool startParsing = false;
    string line;


    while (getline(iss, line))
    {

        if (line.find("module name is") != string::npos)
        {
            startParsing = true;
            continue;
        }
        if (!startParsing)
            continue;
        if (line.empty() || line[0] == ' ')
            break;

        istringstream lineStream(line);
        int index;
        string dummy,type, name, port0, port1, port2;
        
        lineStream >> index >> dummy >> type >> name >> port0 >> port1 >> port2;
        //std::cout << type << std::endl;
        
        if (type != "not1")
        {
            //std::cout << port2 << std::endl;
            /*** 
            gate.port0 = port0;
            gate.port1 = port1;
            gate.port2 = port2;
            ***/
            //cout<< index << endl;
            graph.addEdge(port1,name);
            graph.addEdge(port2,name);
            graph.addEdge(name,port0);
            //std::cout << port2 << std::endl;
            gates[name].push_back(type);
            gates[name].push_back(port0);
            gates[name].push_back(port1);
            gates[name].push_back(port2);
        }
        else
        {
            /*** 
            gate.port0 = port0;
            gate.port1 = port1;
            ***/
            graph.addEdge(port1, name);
            graph.addEdge(name, port0);
            gates[name].push_back(type);
            gates[name].push_back(port0);
            gates[name].push_back(port1);
        }  
        //addGates(gate,gates);
        //std::cout << gate.type << std::endl;
    }
}


