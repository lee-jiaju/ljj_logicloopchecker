#pragma once
#include <string>
#include <vector>
#include <unordered_map>



class Gate
{
public:
    /* data */
    std::string type;
    std::string name;


    std::string port0;
    std::string port1;
    std::string port2;
    Gate(){};
    Gate(std::string type, std::string name);
    Gate(const Gate& other) ;
};
//extern std::unordered_map<std::string,Gate> gates;

//void addGates(const Gate gate,std::unordered_map<std::string,std::vector<std::string>>& gates);