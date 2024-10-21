#include "gateInfo.h"
#include <iostream>


Gate::Gate(std::string type, std::string name)
{
    this->type = type;
    //std::cout << this->type << std::endl;
    this->name = name;
}


Gate::Gate(const Gate& other) {
    this->type = other.type;
    this->name = other.name;
    this->port0 = other.port0;
    this->port1 = other.port1;
    this->port2 = other.port2;
}
/***
void addGates(std::string& name, std::unordered_map<std::string, std::vector<std::string>> &gates)
{
    gates[name] = ;
    std::cout << gates[gate.name].type << std::endl;
}
***/