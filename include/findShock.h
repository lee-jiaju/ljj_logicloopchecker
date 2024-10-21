#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <math.h>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include "Graph.h"
#include "gateInfo.h"
#include "writeCycletoFile.h"

void findShock(std::map<int, std::set<std::string>> &signal_sets, std::map<int, std::set<std::string>> &gate_sets,
               std::map<int, std::set<std::string>>  &loop_other_signals, std::unordered_map<std::string, std::vector<std::string>> &gates,
               std::vector<int> &shock_location, const std::string &filename1, const std::string &filename2);
int gateOutput(std::string& current_gatetype, bool case_condition, int shock, bool current_input);

