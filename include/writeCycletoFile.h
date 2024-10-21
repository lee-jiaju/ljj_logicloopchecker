#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "gateInfo.h"

void writeCycleToFile(Graph &G, const std::string filename, std::unordered_map<std::string, std::vector<std::string>>& all_gates,
                      std::map<int, std::set<std::string>> &signal_sets, std::map<int, std::set<std::string>> &gate_sets, std::map<int, std::set<std::string>> &other_signal_sets);


