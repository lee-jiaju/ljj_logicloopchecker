#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "Graph.h"
#include "gateInfo.h"

void runCommand(const std::string& cmd,std::string& output);
void parseVerilogFile(const std::string& output, Graph &graph,std::unordered_map<std::string,std::vector<std::string>>& gates);